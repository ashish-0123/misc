#!/usr/bin/python

class Node(object):

    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

    def insert(self, data):
        if data < self.data:
            if not self.left:
                self.left = Node(data)
            else:
                self.left.insert(data)
        elif data > self.data:
            if not self.right:
                self.right = Node(data)
            else:
                self.right.insert(data)
               
    def printTreeInOrder(self):
        if self.left:
            self.left.printTreeInOrder()

        print self.data

        if self.right:
            self.right.printTreeInOrder()

    def printTreePreOrder(self):
        print self.data

        if self.left:
            self.left.printTreePreOrder()

        if self.right:
            self.right.printTreePreOrder()

    def printTreePostOrder(self):

        if self.left:
            self.left.printTreePostOrder()

        if self.right:
            self.right.printTreePostOrder()


        print self.data

def printTreeLevelOrder(root):
    queue = []
    level = 0
    print " ---- level {} -----".format(level)
    queue.insert(0, root)
    queue.insert(0, 1)

    while len(queue):
        node = queue.pop()
        if isinstance(node, int):
            if len(queue):
                queue.insert(0, 1)
                level += 1
                print " ---- level {} -----".format(level)
            continue
        print node.data
        if node.left:
            queue.insert(0, node.left)
        if node.right:
            queue.insert(0, node.right)

if __name__ == '__main__':
    r = Node(6)
    r.insert(5)
    r.insert(7)
    r.insert(4)
    r.insert(8)
    r.insert(3)
    r.insert(9)

    print "In Order ----"
    r.printTreeInOrder()
    print "\nPre Order ----"
    r.printTreePreOrder()
    print "\nPost Order ----"
    r.printTreePostOrder()

    print "\nLevel order ----"
    printTreeLevelOrder(r)
