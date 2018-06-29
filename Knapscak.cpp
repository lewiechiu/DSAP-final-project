#include <iostream>
using namespace std;

int max(int a, int b) { return (a > b)? a : b; }
int knapSack(int W, int wt[], int val[], int n)
{




    /*


    I will receive

    first I need to read in all of the mission pointer
    then, I need to acquire all of the mission ShiPeiDu and their name combined in a string array
    After that, we acquire the mission cost of time to start the algorithm
    */
	int i, w;
    int K[n + 1][W + 1] = {0};
    for (i = 0; i <= n; i++)
	{
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    int res = K[n][W];
    cout << res << endl;
    /*
    Now I need to take out the chosen and leave the unchosen one out
    (1) whenever you take out one you should add it into the chosen string of name
    (2) Or, you can simply return
    */
    w = W;
    for (i = n; i > 0 && res > 0; i--)
	{
        if (res == K[i - 1][w] )
            continue;
        else
        {
            cout << wt[i-1] << " ";
            res = res - val[i - 1];
            w = w - wt[i - 1];
        }
    }
}
/*
int main()
{
	int n = 5,w =15;
	int wt[] = {7,3,4,6,8};
	int val[] = {6,9,7,8,5};
	knapSack(w,wt,val,n);
	//w is the upper limit of the weight
	//wt is the array that store the  weight
	//val is the array that stores the value of an single item
	//n is the count of how many elements
    system("pause");
	return 0;
}
*/
