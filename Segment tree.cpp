#include <iostream>
#include <climits>

using namespace std;

int a[10005];
int seg[4 * 10005];    // segment tree

// Build the segment tree
void build(int index, int low, int high) {
    if (low == high) {
        seg[index] = a[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * index + 1, low, mid);
    build(2 * index + 2, mid + 1, high);
    seg[index] = max(seg[2 * index + 1], seg[2 * index + 2]);
}

// Query the segment tree for the maximum value in a range
int query(int index, int low, int high, int left, int right) {
    if (low >= left && high <= right) {
        return seg[index];  // completely contained
    }
    if (high < left || low > right) {
        return INT_MIN;  // no overlap
    }
    // overlap
    int mid = (low + high) / 2;
    int left_query = query(2 * index + 1, low, mid, left, right);
    int right_query = query(2 * index + 2, mid + 1, high, left, right);
    return max(left_query, right_query);
}

int main() {
    int n;
    cout << "Size: ";
    cin >> n;

    cout << "Elements: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(0, 0, n - 1);  // Build the segment tree

    int q;
    cout << "Queries: ";
    cin >> q;

    
    while (q--) {
        int l, r;
        cout << "Left and Right: ";
        cin >> l >> r;
        // Convert 1-based index to 0-based
        cout << "Max element in given range: " << query(0, 0, n - 1, l, r) << endl;
    }

    return 0;
}
