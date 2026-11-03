#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

struct RandSeed {
    RandSeed() { std::srand(std::time(nullptr)); }
} randSeed;


class double_die {
public:
    struct Result {
        int dice_1;
        int dice_2;
        int sum;
    };

    vector<double_die::Result> dices(int num_rolls, int sides) {
        vector<double_die::Result> list_of_results;

        double_die::Result results;
        for (int i =0; i < num_rolls; i++) {
            int dice_1 = rand() % sides + 1;
            int dice_2 = rand() % sides + 1;

            results.dice_1 = dice_1;
            results.dice_2 = dice_2;

            results.sum = results.dice_1 + results.dice_2;
        
            list_of_results.push_back(results);
        }

        return list_of_results;
    }
};