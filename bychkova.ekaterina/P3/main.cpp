#include <iostream>
using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;
  int a[10000];
  int b[10000];

  for (int i = 0; i < n * m; i++) {
    cin >> a[i];
    b[i] = a[i];
  }

  int top = 0;
  int bottom = n - 1;
  int left = 0;
  int right = m - 1;
  int k = 1;

  while (top <= bottom && left <= right) {
    for (int i = bottom; i >= top; i--) {
      b[i * m + left] -= k++;
    }
    left++;
    if (left > right) {
      break;
    }

    for (int j = left; j <= right; j++) {
      b[top * m + j] -= k++;
    }
    top++;
    if (top > bottom) {
      break;
    }

    for (int i = top; i <= bottom; i++) {
      b[i * m + right] -= k++;
    }
    right--;
    if (left > right) {
      break;
    }

    for (int j = right; j >= left; j--) {
      b[bottom * m + j] -= k++;
    }
    bottom--;
  }

  for (int i = 0; i < n * m; i++) {
    cout << b[i] << " ";
  }
  cout << endl;

  int count = 0;

  for (int i = 0; i < n; i++) {
    bool good = true;

    for (int j = 1; j < m; j++) {
      if (a[i * m + j] == a[i * m + j - 1]) {
        good = false;
        break;
      }
    }

    if (good) {
      count++;
    }
  }

  cout << count << endl;
  return 0;
}
