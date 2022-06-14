#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

enum CoinWeight {
	UN_WEIGHT,
    LIGHT_WEIGHT,
    NORMAL_WEIGHT,
    HEAVY_WEIGHT,
};


void simulation(std::string *left, std::string *right, std::string *result, int candidate, int candidate_weight, std::ostream &os)
{
    bool candidate_flag = true;

    for (int wieght = 0; wieght < 3; wieght++) {
        int right_wieght = 0;
        int left_wieght = 0;
        if ((result[wieght].compare("up") == 0) || (result[wieght].compare("down") == 0)) {

            for (char &c : right[wieght]) {
                if (candidate == int(c) - 65) {
                    right_wieght += candidate_weight;
                } else
                    right_wieght += NORMAL_WEIGHT;
            }

            for (char &c : left[wieght]) {
                if (candidate == int(c) - 65) {
                    left_wieght += candidate_weight;
                } else
                    left_wieght += NORMAL_WEIGHT;
            }

            if  ((result[wieght].compare("up") == 0) && (left_wieght <= right_wieght)) {
                candidate_flag = false;
                break;
            }

			if ((result[wieght].compare("down") == 0) && (left_wieght >= right_wieght)) {
				candidate_flag = false;
				break;
			}
        }
    }

    if (candidate_flag) {
        if (candidate_weight == LIGHT_WEIGHT) {
            os << char(65 + candidate) << " is the counterfeit coin and it is light.\n";
        } else {
            os << char(65 + candidate) << " is the counterfeit coin and it is heavy.\n";
        }
    }
}

void find_counterfeit_coin(std::string *left, std::string *right, std::string *result, std::ostream &os)
{
    int coin_weight[12] = { 0 };

    for (int weight = 0; weight < 3; weight++) {
        if (result[weight].compare("even") == 0) {

            for (char &c : right[weight]) {
                coin_weight[int(c) - 65] = NORMAL_WEIGHT;
            }

            for (char &c : left[weight]) {
                coin_weight[int(c) - 65] = NORMAL_WEIGHT;
            }
        }
    }

    for (int candidate = 0; candidate < 12; candidate++) {
        if (coin_weight[candidate] == 0) {
            simulation(left, right, result, candidate, LIGHT_WEIGHT, os);
            simulation(left, right, result, candidate, HEAVY_WEIGHT, os);
        }
    }
}

void uva608(std::istream &is, std::ostream &os)
{
    while (true) {
        std::string line;
        std::getline(is, line);

        int number = atoi(line.c_str());
        if (number <= 0)
            break;

        for (int i = 0; i < number; i++) {
            std::string left[3], right[3], result[3];
            for (int weight = 0; weight < 3; weight++) {
                std::getline(is, line);
                std::stringstream sstream(line);
                std::getline(sstream, left[weight], ' ');
                std::getline(sstream, right[weight], ' ');
                std::getline(sstream, result[weight], ' ');
            }
            find_counterfeit_coin(left, right, result, os);
        }
    }
}

int main(int argc, char **argv)
{
    std::istringstream iss(R"--(1
ABC DEF up
GHI JKL even
EF DA up
)--");

    std::istringstream iss2(R"--(1
ABC FGJ down
DC HG down
ABIHG JKEDF up
)--");

#ifdef GTEST
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    //uva608(iss, std::cout);
    uva608(std::cin, std::cout);
#endif

    return 0;
}
