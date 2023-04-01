
int search(int *a, const int x, const int left, const int right)
{//使用递归的方式
    if (left <= right) {
        int middle = (left + right) / 2;
        if (x < a[middle])
            return search(a, x, left, middle - 1);
        else if (x > a[middle])
            return search(a, x, middle + 1, right);
        else
            return middle;
    }

    return -1;
}