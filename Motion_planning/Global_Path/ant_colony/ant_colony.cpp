#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

const int N = 5; // Number of cities
const int ANT_COUNT = 10;
const int MAX_ITER = 100;
const double ALPHA = 1.0; // Pheromone importance
const double BETA = 5.0;  // Distance importance
const double RHO = 0.5;   // Pheromone evaporation
const double Q = 100.0;   // Pheromone deposit factor

double dist[N][N] = {
    {0, 2, 9, 10, 7},
    {1, 0, 6, 4, 3},
    {15, 7, 0, 8, 3},
    {6, 3, 12, 0, 11},
    {9, 7, 5, 6, 0}
};

double pheromone[N][N];

struct Ant {
    vector<int> tour;
    vector<bool> visited;
    double length;

    Ant() : tour(), visited(N, false), length(0) {}
};

void init_pheromone() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            pheromone[i][j] = 1.0;
}

int select_next_city(const Ant& ant, int current) {
    vector<double> prob(N, 0.0);
    double sum = 0.0;
    for (int j = 0; j < N; ++j) {
        if (!ant.visited[j]) {
            prob[j] = pow(pheromone[current][j], ALPHA) * pow(1.0 / (dist[current][j] + 1e-6), BETA);
            sum += prob[j];
        }
    }
    double r = ((double) rand() / RAND_MAX) * sum;
    double acc = 0.0;
    for (int j = 0; j < N; ++j) {
        if (!ant.visited[j]) {
            acc += prob[j];
            if (acc >= r) return j;
        }
    }
    // fallback
    for (int j = 0; j < N; ++j)
        if (!ant.visited[j]) return j;
    return -1;
}

void update_pheromone(const vector<Ant>& ants) {
    // Evaporation
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            pheromone[i][j] *= (1.0 - RHO);

    // Deposit
    for (const auto& ant : ants) {
        for (int k = 0; k < N; ++k) {
            int from = ant.tour[k];
            int to = ant.tour[(k + 1) % N];
            pheromone[from][to] += Q / ant.length;
            pheromone[to][from] += Q / ant.length;
        }
    }
}

int main() {
    srand(time(0));
    init_pheromone();

    vector<int> best_tour;
    double best_length = numeric_limits<double>::max();

    for (int iter = 0; iter < MAX_ITER; ++iter) {
        vector<Ant> ants(ANT_COUNT);
        for (auto& ant : ants) {
            int start = rand() % N;
            ant.tour.push_back(start);
            ant.visited[start] = true;
            int current = start;
            for (int step = 1; step < N; ++step) {
                int next = select_next_city(ant, current);
                ant.tour.push_back(next);
                ant.visited[next] = true;
                ant.length += dist[current][next];
                current = next;
            }
            // Return to start
            ant.length += dist[current][start];
        }

        // Update best
        for (const auto& ant : ants) {
            if (ant.length < best_length) {
                best_length = ant.length;
                best_tour = ant.tour;
            }
        }

        update_pheromone(ants);
    }

    cout << "Best tour length: " << best_length << endl;
    cout << "Best tour: ";
    for (int city : best_tour) cout << city << " ";
    cout << best_tour[0] << endl; // return to start
    return 0;
}