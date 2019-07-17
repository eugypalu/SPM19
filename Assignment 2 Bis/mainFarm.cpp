/*
    Esecuzione:
    make main
    ./main.o numeroTask lunghezzaTask nWorker seed
*/
#include <chrono>
#include <ff/farm.hpp>
#include <ff/ff.hpp>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include "testprime.cpp"
using namespace ff;
using namespace std;

/*
    Il primo stage della farm crea il set di task su cui voglio lavorare
    Devo creare un numero di task pari a numTask e ogni task ha una dimensione massima
    pari a maxLen.
    Viene mandato in output una coppia <int, int> dove il primo intero indica il task da 
    eseguire e il secondo all'inizio è -1 e poi verrà aggiornato con il valore che viene calcolato
*/
struct firstStage : ff_node_t<pair<int, int>> {
    firstStage(const size_t numTask, const int maxLen, int seed) : numTask(numTask), maxLen(maxLen), seed(seed) {}

    pair<int, int> *svc(pair<int, int> *) {
        srand(seed);
        for (size_t i = 0; i < numTask; ++i) {
            ff_send_out(new pair<int, int>(rand() % maxLen, -1));
        }
        return EOS;
    }

    int seed;
    const size_t numTask;
    const int maxLen;
};

/*
    Il secondo stage della farm deve estrarre il task, cercare di capire quanti sono i primi 
    nell'intervallo preso in considerazione e poi manda in output la coppia <task, numeroPrimi nell'intervallo>
*/

struct secondStage : ff_node_t<pair<int, int>> {
    pair<int, int> *svc(pair<int, int> *task) {
        pair<int, int> &primes = *task;

        int original = primes.first;
        int numPrimi = primes_to(original);

        return new pair<int, int>(original, numPrimi);
    }
};

/*
    Il terzo stage prende la coppia e la memorizza in un vettore.
    Quando finisce di estrarre i dati allora legge il contenuto 
    del vettore e lo stampa.
*/
struct thirdStage : ff_node_t<pair<int, int>> {
    pair<int, int> *svc(pair<int, int> *task) {
        pair<int, int> &t = *task;
        result.push_back(t);
        delete task;
        return GO_ON;
    }

    void printVector(vector<pair<int, int>> vct) {
        for (int i = 0; i < vct.size(); i++) {
            cout << "Task: " << vct[i].first << " Number of primes:" << vct[i].second << endl;
        }
    }

    //void svc_end() { printVector(result); }
    vector<pair<int, int>> result;
};

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cout << "Usage is: " << argv[0] << " m n nw seed" << endl;
        return (-1);
    }

    int m = atoi(argv[1]);       // Quanti task
    int maxLen = atoi(argv[2]);  // Dimensione singolo task
    int nw = atoi(argv[3]);      // Numero worker
    int seed = atoi(argv[4]);    // il seed per il calcolo random dei task

    if (nw > 0) {
        firstStage emitter(m, maxLen, seed);
        thirdStage collector;

        std::vector<std::unique_ptr<ff_node>> W;
        for (size_t i = 0; i < nw; ++i)
            W.push_back(make_unique<secondStage>());
        ff_Farm<float> farm(std::move(W), emitter, collector);

        {
            utimer tpar("par nw = " + to_string(nw) + " m= " + to_string(m) + " max= " + to_string(maxLen));
            if (farm.run_and_wait_end() < 0) {
                error("running farm");
                return -1;
            }
            ffTime(STOP_TIME);
        }
    }

    return 0;
}