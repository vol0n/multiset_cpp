#include <iostream>
#include "funcs.h"
#include "Inputfuncs.h"

using namespace std;
set unvr;
u_int len_of_code;

int main() {
    srand(time(nullptr));

    set opS;
    set Sets[2];
    auto printsets = [&Sets](){cout << "Set 1: " << Sets[0] << "Set 2: " << Sets[1];};
    string buf;
    buf = 'n';

    while (true) {
        switch (buf[0]) {

            case 'q':
                return 0;
                //Задание множеств

            case 'n':{
                short N = takeNum(0, 15, buf, "\nType in the number of elements in a set, min = 0, max = 15: ");
                if (N) {
                    len_of_code = N;
                    size_t cardinality = pow(2, N);// количество элементов в универсуме
                    u_int max_elem = cardinality-1;// максимальный номер элемента
                    // mults - для формирования кратностей от пользователя, elems - для формирования элементов множества
                    vector<u_int> elems, mults;
                    // max_mults - массив максимальных кратностей для элементов универсума.
                    vector<u_int> max_mults = generateVector(1, max_elem*max_elem, cardinality, false);

                    // удаление старого универсума от старого ввода пользователя
                    unvr.clear();
                    unvr.reserve(cardinality);
                    for (u_int i = 0; i < cardinality; i++)
                        unvr.emplace_back(i, max_mults[i]);
                    cout << "UNIVERSUM:" << unvr;

                    bool IsByHand = takeNum(0, 1, buf,
                                            "Do you wish to generate sets (0) or choose elements manually (1): ");
                    bool IsByHandMul = takeNum(0, 1, buf,
                                            "Do you wish to generate multiplicities (0) or choose them manually (1): ");
                    u_int sizes[2];
                    sizes[0] = takeNum(0, cardinality, buf, "Type in number of elements in the first set: ");
                    sizes[1] = takeNum(0, cardinality, buf, "Type in number of elements in the second set: ");

                    for (short j = 0; j < 2; j++) {
                        if (sizes[j] == 0){
                            Sets[j] = empty_set();
                            continue;
                        }
                        if (IsByHand) {
                            elems = takeNums(0, vector<u_int>(1, max_elem), sizes[j],
                                             "Type in the numbers of elements separated by space: ",
                                             true);
                        } else {
                            elems = generateVector(0, max_elem, sizes[j]);
                        }
                        if (IsByHandMul) {
                            vector<u_int> max_mul(elems.begin(), elems.end());
                            for (auto&& i : max_mul)
                                i = max_mults[i];
                            mults = takeNums(1, max_mul, sizes[j], "Type in the multiplicities: ", false);
                        }
                        else
                            mults = generateMults(max_mults, elems);
                        Sets[j] = create_set(sizes[j], std::move(elems), std::move(mults));
                    }
                }

                else{
                    unvr = set(1, Pair(0, 0));
                    cout << "UNIVERSUM:" << unvr;
                    Sets[0] = empty_set();
                    Sets[1] = empty_set();
                }
                printsets();
                printMenu();
                break;
            }

            case '1':
                printsets();
                calc_print("Union of sets: ", calc_union, Sets[0], Sets[1]); break;

            case '2':
            {
                printsets();
                calc_print("Intersect of sets", calc_intersect, Sets[0], Sets[1]); break;
            }

            case '3':{
                printsets();
                calc_print("Symmetric difference of sets", calc_symdif, Sets[0], Sets[1]); break;
            }

            case '4':{
                printsets();
                calc_print("The complement of the first set: ", calc_complement, Sets[0]);
                calc_print("The complement of the second set: ", calc_complement, Sets[1]); break;
            }

            case '5':{
                printsets();
                calc_print("The difference Sets[0] \\ Sets[1]: ", calc_dif, Sets[0], Sets[1]); break;
            }

            case '6':{
                printsets();
                calc_print("The difference Sets[1] \\ Sets[0]: ", calc_dif, Sets[1], Sets[0]); break;
            }

            case '7':{
                printsets();
                calc_print("The sum of sets ", calc_sum, Sets[0], Sets[1]); break;
            }

            case '8':{
                printsets();
                u_int x = takeNum(0, unvr.size()-1, buf, "Type in the number: ");
                opS = multiply(Sets[0], x);
                cout << "Multiplication on number Set 1: " << opS;
                opS = multiply(Sets[1], x);
                cout << "Multiplication on number Set 2: " << opS;
                break;
            }

            case '9':{
                printsets();
                calc_print("\nMultiplication of sets: ", multiply, Sets[0], Sets[1]); break;
            }

            case 'p':{
                printsets();
                u_int x = takeNum(0, unvr.size()-1, buf, "Type in the number: ");
                opS = pow_set(x, Sets[0]);
                cout << "Set 1 raised to power " << x << opS;
                opS = pow_set(x, Sets[1]);
                cout << "Set 2 raised to power " << x << opS;
                break;
            }
            case 's': printsets(); break;
            case 'm': printMenu(); break;
            case 'u': cout << "UNIVERSUM:" << unvr; break;
            default: cout << buf[0] << " no such command." << endl;
        }

        cout << "Command: ";
        takeInput(buf);

    }
}



