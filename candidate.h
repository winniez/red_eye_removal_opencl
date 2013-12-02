#include<vector>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

class Candidate 
{
public:
    int cox;
    int coy;
    int score;
    int clusterSize;
    
    Candidate(int x, int y, int s)
    {
        cox = x;
        coy = y;
        score = s;
        clusterSize = 1;
    }
    Candidate()
    {
        cox = 0;
        coy = 0;
        score = 0;
        clusterSize = 1;
    }
    ~Candidate(){}

};


void find_match_candidates(int* sortedScores, int* unsortedScores, int sortSize, int size, int cols, int rows)
{
    vector<Candidate> final;
    int visited[size];
    for (int i = 0; i < size; i++)
    {
        visited[i] = 0;
    }

    vector<Candidate> candidates;
    int tmps, tmpx, tmpy, dist;
    // get top
    tmps = sortedScores[sortSize-1];
    // get index
    for ( int i = 0; i < size; i++)
    {
        if (unsortedScores[i] == tmps && visited[i] == 0)
        {
           tmpx = i % cols;
           tmpy = (int) ( i / cols);
           visited[i] = 1;
           break;
        }
    }
    Candidate newcandidate = Candidate(tmpx, tmpy, tmps);
    candidates.push_back(newcandidate);
    // terminate condition
    
    int k = sortSize - 2;
    while (sortedScores[k] > (int)(0.8 * sortedScores[size - 1]))
    {
        tmps = sortedScores[k];
        for (int i = 0; i < size; i++)
        {
            if (unsortedScores[i] == tmps && visited[i] == 0)
            {
                tmpx = i % cols;
                tmpy = (int) (i / cols);
                visited[i] = 1;
                break;
            }
        }
        // check if within known cluster
        int flag = 0;
        for (int j = 0; j < candidates.size(); j++)
        {
            dist = abs(candidates[j].cox - tmpx) + abs(candidates[j].coy - tmpy);
            if (dist < 33)
            {
                candidates[j].clusterSize++;
                flag = 1;
                break;
            }
        }
        if (!flag)
        {// new cluster
            Candidate newcandidate = Candidate(tmpx, tmpy, tmps);
            candidates.push_back(newcandidate);
        }
        k--;
    }
    printf("candidate cluster num:%d\n", (int)candidates.size());
    for (int i = 0; i < candidates.size(); i++)
    {
        printf("candidate %d: X %d, Y %d, score %d, num %d\n", i, candidates[i].cox, candidates[i].coy, candidates[i].score, candidates[i].clusterSize);
    }

}


