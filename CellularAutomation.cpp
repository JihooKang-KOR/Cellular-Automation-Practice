#include "CellularAutomation.h"
#include <random>

CellularAutomation::CellularAutomation(int k, int r, int N) // Constructor for CA1D
: k(k), r(r), m(2*r + 1), N(N), bin(pow(k, m), 0), state(N*N, 0)
{
    for(int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            this->coord.emplace_back(i, N - j, 0);
        }
    }
}

CellularAutomation::CellularAutomation(int N) : N(N), state((N+2)*(N+2), 0), finalstate(N*N, 0)
{
    for(int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            this->coord.emplace_back(i, j, 0);
        }
    }
}

std::vector<Vec3> CellularAutomation::getPoint()
{
    return this->coord;
}

std::vector<std::vector<int>> CellularAutomation::getCellNumber()
{
    for (int j = 0; j < this->N - 1; j++)
    {
        for (int i = 0; i < this->N - 1; i++)
            this->cell.push_back({i + j * this->N, (i + 1) + j * this->N, (i + 1) + (j + 1) * this->N, i + (j + 1) * this->N});
        //this->cell.push_back({j});
    }
    return this->cell;
}

std::vector<double> CellularAutomation::cellular1D(int rulenum)
{
    int dec;

    for(int j = 0; rulenum != 0; j++)
    {
        this->bin[j] = rulenum%2;
        rulenum = int(rulenum/2);
    }

    std::vector<int>::iterator ptr;
    for(ptr = this->bin.end() - 1; ptr >= this->bin.begin(); ptr--)
        std::cout << *ptr << " ";
    std::cout << std::endl;

    //std::vector<int> state{1,0,1,1,0,1,0,1,1,0,1,0,1,1,0};
    //std::vector<int> state{1,0,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1);
    for(int p = 0; p < this->N; p++)
    {
        this->state[p] = dis(gen);
    }
    //this->state[int(N)-1] = 1;
    std::vector<double> statedump(N, 0);
    for(int l = 0; l < statedump.size(); l++)
        statedump[l] = this->state[l];

    for(int iter = 0; iter < this->N - 1; iter++)
    {
        dec = (0*2 + this->state[0 + this->N*iter])*2 + this->state[1 + this->N*iter];
        statedump[0] = this->bin[dec];
        for(int i = 1; i < statedump.size() - 1; i++)
        {
            dec = (this->state[i-1 + this->N*iter]*2 + this->state[i + this->N*iter])*2 + this->state[i+1 + this->N*iter];
            statedump[i] = this->bin[dec];
        }
        dec = (this->state[statedump.size()-2 + this->N*iter]*2 + this->state[statedump.size()-1 + this->N*iter])*2 + 0;
        statedump[statedump.size()-1] = this->bin[dec];

        for(int k = 0; k < statedump.size() - 1; k++)
            this->state[k + (iter+1)*this->N] = statedump[k];
    }

    return this->state;
}

std::vector<double> CellularAutomation::gameOfLife(int iter)
{
    /*std::random_device rd; // random initialization
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1);
    for(int q = 1; q <= this->N; q++)
    {
        for (int p = 1; p <= this->N; p++)
        {
            this->state[p + q*this->N] = dis(gen);
        }
    }*/

    // Glider gun initialization
    this->state[2 + this->N*(this->N - 6)] = 1; this->state[3 + this->N*(this->N - 6)] = 1;
    this->state[2 + this->N*(this->N - 7)] = 1; this->state[3 + this->N*(this->N - 7)] = 1;

    this->state[14 + this->N*(this->N - 4)] = 1; this->state[15 + this->N*(this->N - 4)] = 1;
    this->state[13 + this->N*(this->N - 5)] = 1; this->state[17 + this->N*(this->N - 5)] = 1;
    this->state[12 + this->N*(this->N - 6)] = 1; this->state[18 + this->N*(this->N - 6)] = 1;
    this->state[12 + this->N*(this->N - 7)] = 1; this->state[16 + this->N*(this->N - 7)] = 1;
    this->state[18 + this->N*(this->N - 7)] = 1; this->state[19 + this->N*(this->N - 7)] = 1;
    this->state[12 + this->N*(this->N - 8)] = 1; this->state[18 + this->N*(this->N - 8)] = 1;
    this->state[13 + this->N*(this->N - 9)] = 1; this->state[17 + this->N*(this->N - 9)] = 1;
    this->state[14 + this->N*(this->N - 10)] = 1; this->state[15 + this->N*(this->N - 10)] = 1;

    this->state[26 + this->N*(this->N - 2)] = 1;
    this->state[24 + this->N*(this->N - 3)] = 1; this->state[26 + this->N*(this->N - 3)] = 1;
    this->state[22 + this->N*(this->N - 4)] = 1; this->state[23 + this->N*(this->N - 4)] = 1;
    this->state[22 + this->N*(this->N - 5)] = 1; this->state[23 + this->N*(this->N - 5)] = 1;
    this->state[22 + this->N*(this->N - 6)] = 1; this->state[23 + this->N*(this->N - 6)] = 1;
    this->state[24 + this->N*(this->N - 7)] = 1; this->state[26 + this->N*(this->N - 7)] = 1;
    this->state[26 + this->N*(this->N - 8)] = 1;

    this->state[36 + this->N*(this->N - 4)] = 1; this->state[37 + this->N*(this->N - 4)] = 1;
    this->state[36 + this->N*(this->N - 5)] = 1; this->state[37 + this->N*(this->N - 5)] = 1;
    // ---------------------------------------------------------------------------------------

    /*this->state[1 + this->N*(this->N - 1)] = 1; this->state[2 + this->N*(this->N - 2)] = 1;
    this->state[1 + this->N*(this->N - 3)] = 1; this->state[2 + this->N*(this->N - 3)] = 1;
    this->state[3 + this->N*(this->N - 1)] = 1;*/

    std::vector<double> statedump = this->state;

    double sum;
    for(int itr = 0; itr < iter; itr++)
    {
        for (int j = 1; j < this->N + 1; j++)
        {
            for (int i = 1; i < this->N + 1; i++)
            {
                sum = statedump[(i - 1) + (j - 1) * this->N] + statedump[i + (j - 1) * this->N] +
                      statedump[(i + 1) + (j - 1) * this->N]
                      + statedump[(i - 1) + j * this->N] + statedump[(i + 1) + j * this->N]
                      + statedump[(i - 1) + (j + 1) * this->N] + statedump[i + (j + 1) * this->N] +
                      statedump[(i + 1) + (j + 1) * this->N];

                if (this->state[i + j * this->N] == 1 && (sum == 2 || sum == 3))
                    this->state[i + j * this->N] = 1;
                else if (this->state[i + j * this->N] == 0 && sum == 3)
                    this->state[i + j * this->N] = 1;
                else
                    this->state[i + j * this->N] = 0;
            }
        }
        statedump = this->state;
    }
    /*std::vector<double>::iterator ptr;
    for(ptr = this->state.begin(); ptr < this->state.end(); ptr++)
        std::cout << *ptr << " ";*/

    for(int l = 0; l < this->N; l++)
    {
        for (int k = 0; k < this->N; k++)
            this->finalstate[k + l*this->N] = this->state[k+1 + (l+1)*this->N];
    }

    return this->finalstate;
}

CellularAutomation::~CellularAutomation()
{ }