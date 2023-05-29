//implement Min, Max, Sum, Average operations using parallel reduction

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

//function prototypes
void initialize(int *a, int n);
void print(int *a, int n);
void mmsa(int *a, int n, int &min, int &max, int &sum, double &avg);

int main(int argc, char *argv[])
{
    int n; cout << "Enter n: "; cin >> n;
    int *a = new int[n];
    int min, max, sum;
    double avg;
    double start, end;

    initialize(a, n);
    //print(a, n);

    start = omp_get_wtime();
    mmsa(a, n, min, max, sum, avg);
    end = omp_get_wtime();

    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << "Sum: " << sum << endl;
    cout << "Avg: " << avg << endl;
    cout << "Time: " << end - start << endl;

    delete[] a;
    return 0;
}

void initialize(int *a, int n)
{
    cout << "Enter " << n << " numbers: " << endl;
    for (int i = 0; i < n; i++)
        cin >> a[i];
}

void print(int *a, int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

void mmsa(int *a, int n, int &min, int &max, int &sum, double &avg)
{
    min = a[0];
    max = a[0];
    sum = 0;
    avg = 0.0;

    //parallel reduction
    #pragma omp parallel for reduction(min:min) reduction(max:max) reduction(+:sum)
    for (int i = 0; i < n; i++)
    {
        if (a[i] < min)
            min = a[i];
        if (a[i] > max)
            max = a[i];
        sum += a[i];
    }
    avg = (double)sum / n;
}

