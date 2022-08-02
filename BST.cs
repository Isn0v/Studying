using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BST
{
    internal class BST<T> : IEnumerable<Node<T>> where T : IComparable<T>, IEquatable<T>
    {
        private Node<T>? header;
        private int length;

        private Node<T>? Header => header;
        public int Length
        {
            get => length;
        }
        

        public BST(T value)
        {
            header = new Node<T>(value);
            length = 1;
        }
        public BST(Node<T> header)
        {
            this.header = header;
            length = 1;
        }
        public BST()
        {
            this.header = null;
            length = 0;
        }


        public bool Contains(T value)
        {
            Node<T> node = new Node<T>(value);
            if (header == null)
            {
                throw new InvalidOperationException("BST has no nodes");
            }
            Node<T> tmp = header;
            while (true)
            {
                if (tmp == node)
                    return true;
                if (node < tmp)
                {
                    if (tmp.Left != null)
                    {
                        tmp = tmp.Left;
                    }
                    else
                    {
                        if (tmp != node)
                            return false;
                    }
                }
                else if (node > tmp)
                {
                    if (tmp.Right != null)
                    {
                        tmp = tmp.Right;
                    }
                    else
                    {
                        if (node != tmp)
                            return false;
                    }
                }
            }
        }
        public void RecursiveAdd(T value)
        {
            length++;
            if (header == null)
            {
                header = new Node<T>(value);
                length--;
            }
            else
            {
                header.RecursiveConnect(new Node<T>(value));
            }
        }
        public void Add(T value)
        {
            length++;
            if (header == null)
            {
                header = new Node<T>(value);
                length--;
            }
            else
            {
                header.Connect(new Node<T>(value));
            }
        }
        public void Remove(T value)
        {
            if (header == null)
            {
                throw new InvalidOperationException("BST isn't initialized");
            }
            length--;
            Node<T> node = new Node<T>(value);
            bool isHeaderChanged = false;
            header.Remove(node, ref isHeaderChanged);
            if (isHeaderChanged)
            {
                header = new Node<T>(header.Left.Parent.Value, null, header.Left, header.Right);
            }
        }


        public List<Node<T>> inOrderTraversalList()
        {
            Node<T>? lastNode = null;
            Node<T>? currentNode = header;
            List<Node<T>> outputList = new List<Node<T>>();
            while(currentNode != null)
            {
                if(lastNode == currentNode.Parent)
                {
                    if (currentNode.Left != null)
                    {
                        lastNode = currentNode;
                        currentNode = currentNode.Left;
                        continue;
                    }
                    else
                    {
                        lastNode = null;
                    }
                }
                if (lastNode == currentNode.Left)
                {
                    outputList.Add(currentNode);
                    if(currentNode.Right != null)
                    {
                        lastNode = currentNode;
                        currentNode = currentNode.Right;
                        continue;
                    }
                    else
                    {
                        lastNode = null;
                    }
                }
                if(lastNode == currentNode.Right)
                {
                    lastNode = currentNode;
                    currentNode = currentNode.Parent;
                }
            }
            return outputList;
        }
        public Node<T> GetValue(int index)
        {
            return inOrderTraversalList()[index];
        }
        public int Search(T value)
        {
            Node<T> tmp = new Node<T>(value);
            List<Node<T>> list = inOrderTraversalList();
            for(int i =0; i < list.Count; i++)
            {
                if(list[i] == tmp)
                {
                    return i;
                }
            }
            return -1;
        }

        public IEnumerator<Node<T>> GetEnumerator() //Здесь могут быть проблемы. Нужно будет обсудить на занятии
        {
            return new BSTIterator<T>(this);
        } 
        IEnumerator IEnumerable.GetEnumerator() //Здесь могут быть проблемы
        {
            return GetEnumerator();
        }

        public override string ToString()
        {
            string Res = "";
            foreach(Node<T> node in this)
            {
                Res += node.ToString() + " ";
            }
            return Res;
        }

        public Node<T> this[int index]
        {
            get => inOrderTraversalList()[index];
            set => inOrderTraversalList()[index] = value;
        }

        class BSTIterator<T> : IEnumerator<Node<T>> where T : IComparable<T>, IEquatable<T>
        {
            private BST<T> bst;
            private int position = -1;

            public Node<T> Current
            {
                get
                {
                    try
                    {
                        return bst[position];
                    }
                    catch (IndexOutOfRangeException)
                    {
                        throw new IndexOutOfRangeException("Index of bst out of Range");
                    }
                }
            }
            object IEnumerator.Current => Current;

            public BSTIterator(BST<T> bst)
            {
                this.bst = bst;
            }
            public bool MoveNext()
            {
                position++;
                return (position < bst.Length);
            }
            public void Reset()
            {
                position = -1;
            }
            public void Dispose() { }
        }
    }

    



}
