#define capacity 501

template<class T>
class MaxHeap
{
private:
    T heap[capacity];
    int index;

    int parent(int pos)
    {
        return (pos-1)/2;
    }
    int leftChild(int pos)
    {
        return 2*pos+1;
    }
    int rightChild(int pos)
    {
        return 2*pos+2;
    }
    void swapAt(int pos1, int pos2)
    {
        T temp = heap[pos1];
        heap[pos1] = heap[pos2];
        heap[pos2] = temp;
    }
    void heapifyUp(int pos)
    {
        while(pos!=0 && heap[pos]>heap[parent(pos)])
        {
            swapAt(pos,parent(pos));
            pos = parent(pos);
        }
    }
    void heapifyDown(int pos)
    {
        int left = leftChild(pos);
        int right = rightChild(pos);
        int ctrl = pos;
        if(left<index && heap[left]>heap[ctrl])
            ctrl = left;
        if(right<index && heap[right]>heap[ctrl])
            ctrl = right;
        if(ctrl != pos)
        {
            swapAt(pos,ctrl);
            heapifyDown(ctrl);
        }
    }
public:
    MaxHeap()
    {
        index = 0;
    }
    void push(T value)
    {
        heap[index] = value;
        heapifyUp(index);
        index++;
    }
    void pop()
    {
        heap[0] = heap[index-1];
        index--;
        heapifyDown(0);
    }
    T top()
    {
        return heap[0];
    }
    int size()
    {
        return index;
    }
    bool empty()
    {
        return index == 0;
    }
};

template<class T>
class MinHeap
{
private:
    T heap[capacity];
    int index;

    int parent(int pos)
    {
        return (pos-1)/2;
    }
    int leftChild(int pos)
    {
        return 2*pos+1;
    }
    int rightChild(int pos)
    {
        return 2*pos+2;
    }
    void swapAt(int pos1, int pos2)
    {
        T temp = heap[pos1];
        heap[pos1] = heap[pos2];
        heap[pos2] = temp;
    }
    void heapifyUp(int pos)
    {
        while(pos!=0 && heap[pos] < heap[parent(pos)])
        {
            swapAt(pos,parent(pos));
            pos = parent(pos);
        }
    }
    void heapifyDown(int pos)
    {
        int left = leftChild(pos);
        int right = rightChild(pos);
        int ctrl = pos;
        if(left<index && heap[left] < heap[ctrl])
            ctrl = left;
        if(right<index && heap[right] < heap[ctrl])
            ctrl = right;
        if(ctrl != pos)
        {
            swapAt(pos,ctrl);
            heapifyDown(ctrl);
        }
    }
public:
    MinHeap()
    {
        index = 0;
    }
    void push(T value)
    {
        heap[index] = value;
        heapifyUp(index);
        index++;
    }
    void pop()
    {
        heap[0] = heap[index-1];
        index--;
        heapifyDown(0);
    }
    T top()
    {
        return heap[0];
    }
    int size()
    {
        return index;
    }
    bool empty()
    {
        return index == 0;
    }
};
