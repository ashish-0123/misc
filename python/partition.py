def partition(arr, low, high):
    i = 0
    j = low
    pivotitem = arr[low]
    
    print arr

    print 'pivotitem = ', pivotitem

    for i in range(low+1, high+1):
        print '\n---({0})-----'.format(arr[i])
        print "i = ", i

        if arr[i] < pivotitem:
            print arr[i], " < ", pivotitem
            j = j + 1
            print "j = ", j
            print "swapping arr[",i,"] and arr[", j, "] (", arr[i], arr[j], ")"
            temp = arr[i]
            arr[i] = arr[j]
            arr[j] = temp
    print "pivotpoint = ", j
    pivotpoint = j
    print "swapping arr[",low,"] and arr[", pivotpoint, "] (", arr[low], arr[pivotpoint], ")"
    temp = arr[low]
    arr[low] = arr[pivotpoint]
    arr[pivotpoint] = temp

    print "returning pivotpoint = ", pivotpoint
    return pivotpoint


if __name__ == '__main__':
    arr = [38,8,10,3,2,80,30,33,1]
    pp = partition(arr, 0, 8)
    print pp
    print arr
