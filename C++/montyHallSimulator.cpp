#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

class MontyHallSimulator {
    public:
        MontyHallSimulator() : winsWithoutSwitching(0), winsWithSwitching(0) {
            std::srand(static_cast<unsigned int>(std::time(0)));
        }
    
        void runSimulations(int simulationQty) {
            for (int run = 0; run < simulationQty; ++run) {
                // Simulate without switching
                if (simulateMontyHall(false))
                    this->winsWithoutSwitching++;
    
                // Simulate with switching
                if (simulateMontyHall(true))
                    this->winsWithSwitching++;
            }
        }
    
        void printResults() const {
            std::cout << "Results after " << (winsWithoutSwitching + winsWithSwitching) << " simulations:\n";
            std::cout << "Wins without switching: " << winsWithoutSwitching << "\n";
            std::cout << "Wins with switching: " << winsWithSwitching << "\n";
        }
    
    private:
        bool simulateMontyHall(bool switchDoor) {
            // Initialize doors with two goats and one car
            // 0 represents a goat, and 1 represents a car
            int doors[] = {0, 0, 1};
    
            // Shuffle the doors randomly, and play the game
            std::shuffle(std::begin(doors), std::end(doors), std::default_random_engine(std::time(0)));
            int playerChoice = std::rand() % 3;
    
            // Host reveals a door with a goat that wasn't chosen
            int doorRevealed;
            do {
                doorRevealed = std::rand() % 3;
            } while (doorRevealed == playerChoice || doors[doorRevealed] == 1);
    
            // Switch to the other unopened door if the player decided to switch
            if (switchDoor)
                playerChoice = 3 - playerChoice - doorRevealed;
    
            // Check if the player won (car is behind their final choice)
            return doors[playerChoice] == 1;
        }
    
        int winsWithoutSwitching;
        int winsWithSwitching;
};

int main() {
    MontyHallSimulator montyHallSimulator;
    montyHallSimulator.runSimulations(100000);
    montyHallSimulator.printResults();

    return 0;
}
