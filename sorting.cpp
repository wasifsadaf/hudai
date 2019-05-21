/*
    Insertion Sort
*/

template<typename T>
void insertionSort(T* begin, T* end, bool (*cmp)(T*, T*))
{
	T temp;
	T* i;
	T* j;
	for(i=begin+1; i<end; i++)
	{
		temp = *i;
		j = i - 1;

		while(j>=begin && cmp(&temp, j))
		{
			*(j+1) = *j;
			j = j - 1;
		}
		*(j+1) = temp;
	}
}

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
