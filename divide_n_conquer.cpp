/*
        Merge Sort
*/
template <typename IT>
void mergesort(IT begin, IT end, IT res, bool (*cmp)(IT, IT))
{
    int s = end - begin;

    if (s > 1)
    {
        IT middle = begin + (s / 2);
        mergesort(begin, middle, res,cmp);
        mergesort(middle, end, res,cmp);

        IT a = begin, b = middle, r = res;

        while (a < middle && b < end)
        {
            if (cmp(a, b))
                *r++ = *a++;
            else
                *r++ = *b++;
        }
        while (a < middle)
            *r++ = *a++;
        while (b < end)
            *r++ = *b++;
        while (begin < end)
            *begin++ = *res++;
    }
}

/*
        Binary Search
*/
template<typename T>
T* b_search(T* begin, T* end, T key, bool (*cmp)(T*, T*)) {
    T* NotFound = end;
    while(begin < end) {
        T* Middle = begin + (end-begin)/2;
        if(*Middle == key)
            return Middle;
        else if(cmp(Middle, &key))
            begin = Middle+1;
        else
            end = Middle;
    }
    return NotFound;
}

/*
        Lower_Bound
*/
template<typename T>
T* low_bound(T* begin, T* end, T key, bool (*cmp)(T*, T*)) {
    while(begin < end) {
        T* Middle = begin + (end-begin)/2;
        if(Middle == &key)
            end = Middle;
        else if(cmp(Middle, &key))
            begin = Middle + 1;
        else
            end = Middle;
    }
    return begin;
}

/*
        Upper_Bound
*/
template<typename T>
T* up_bound(T *begin, T *end, T key, bool (*cmp)(T *, T *)) {
    while(begin < end) {
        T *Middle = begin + (end-begin)/2;
        if(*Middle == key)
            begin = Middle + 1;
        else if (cmp(Middle, &key))
            begin = Middle + 1;
        else
            end = Middle;
    }
    return begin;
}
