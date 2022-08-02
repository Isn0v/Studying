using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BST
{
    internal class Node<T> : IComparable<Node<T>>, IEquatable<Node<T>> where T : IComparable<T>, IEquatable<T>
    {
        private T value;
        private Node<T>? parent;
        private Node<T>? left;
        private Node<T>? right;

        public T Value
        {
            get => value;
            set => this.value = value;
        }
        public Node<T>? Parent
        {
            get => parent;
            set => this.parent = value;
        }
        public Node<T>? Left
        {
            get => left;
            set => this.left = value;
        }
        public Node<T>? Right
        {
            get => right;
            set => this.right = value;
        }

        public Node(T val, Node<T>? parent = null, Node<T>? left = null, Node<T>? right = null)
        {
            value = val;
            this.parent = parent;
            this.left = left;
            this.right = right;
        }

        public void RecursiveConnect(Node<T> node)
        {
            if (Value == null)
            {
                Value = node.Value;
                return;
            }
            if(this == node)
            {
                throw new InvalidOperationException($"BST already has such value: Node<{node.Value.GetType()}>:{node.Value}");
            }
            if(this > node)
            {
                if (left == null)
                {
                    node.Parent = this;
                    left = node;
                }
                else
                {
                    left.RecursiveConnect(node);
                }
            }
            else if(this < node)
            {
                if(right == null)
                {
                    node.Parent = this;
                    right = node;
                }
                else
                {
                    right.RecursiveConnect(node);
                }
            }
        }
        public void Connect(Node<T> node)
        {
            Node<T> tmp = this;
            while (true)
            {
                if(tmp == node)
                {
                    throw new InvalidOperationException($"BST already has such value: " +
                        $"Node<{node.Value.GetType()}>:{node.Value}");
                }
                if(node < tmp)
                {
                    if (tmp.Left == null)
                    {
                        tmp.Left = node;
                        node.Parent = tmp;
                        return;
                    }
                    else
                        tmp = tmp.Left;
                }
                else if(node > tmp)
                {
                    if (tmp.Right == null)
                    {
                        tmp.Right = node;
                        node.Parent = tmp;
                        return;
                    }
                    else
                        tmp = tmp.Right;
                }
            }
        }
        public void Remove(Node<T> node, ref bool isHeaderChanged)
        {
            Node<T>? tmp = this;
            while (true)
            {
                if (node < tmp)
                {
                    if (tmp.Left != null)
                        tmp = tmp.Left;
                    else
                        throw new InvalidOperationException("Can't remove non-existing node");
                }
                else if(node > tmp)
                {
                    if (tmp.Right != null)
                        tmp = tmp.Right;
                    else
                        throw new InvalidOperationException("Can't remove non-existing node");
                }
                else if(node == tmp)
                {
                    if(tmp.Left == null && tmp.Right == null)
                    {
                        if(tmp.Parent == null)
                        {
                            throw new InvalidOperationException("BST can't have no values at all");
                        }
                        else if(tmp.Parent.Left == tmp)
                        {
                            tmp.Parent.Left = null;
                        }
                        else if(tmp.Parent.Right == tmp)
                        {
                            tmp.Parent.Right = null;
                        }
                        return  ;
                        //правильно
                    }
                    else if(tmp.Left != null && tmp.Right == null)
                    {
                        if (tmp.Parent == null)
                        {
                            throw new InvalidOperationException("BST can't have no values at all");
                        }
                        else if (tmp == tmp.Parent.Right)
                        {
                            tmp.Parent.Right = tmp.Left;
                            tmp.Left.Parent = tmp.Parent;
                        }
                        else if(tmp == tmp.Parent.Left)
                        {
                            tmp.Parent.Left = tmp.Left;
                            tmp.Left.Parent = tmp.Parent;
                        }
                        return  ;
                        //по идее правильно
                    }
                    else if(tmp.Left == null && tmp.Right != null)
                    {
                        if (tmp.Parent == null)
                        {
                            throw new InvalidOperationException("BST can't have no values at all");
                        }
                        else if (tmp == tmp.Parent.Right)
                        {
                            tmp.Parent.Right = tmp.Right;
                            tmp.Right.Parent = tmp.Parent;
                        }
                        else if (tmp == tmp.Parent.Left)
                        {
                            tmp.Parent.Left = tmp.Right;
                            tmp.Right.Parent = tmp.Parent;
                        }
                        return  ;
                        //по идее правильно
                    }
                    else if(tmp.Left != null && tmp.Right != null)
                    {
                        Node<T>? tmp2 = tmp.Right;
                        while (tmp2.Left != null)
                        {
                            tmp2 = tmp2.Left;
                        }

                        if (tmp.Parent == null)
                        {
                            isHeaderChanged = true;
                            if (tmp2.Right == null)
                            {
                                Node<T> copied = new Node<T>(tmp2.Value, null, tmp.Left, tmp.Right);
                                tmp.Left.Parent = copied;
                                tmp.Right.Parent = copied;
                                tmp = null;
                            }
                            else
                            {
                                tmp2.Right.Parent = tmp2.Parent;
                                tmp2.Parent.Left = tmp2.Right;
                                Node<T> copied = new Node<T>(tmp2.Value, null, tmp.Left, tmp.Right);
                                tmp.Left.Parent = copied;
                                tmp.Right.Parent = copied;
                                tmp = null;
                            }
                            return;
                        }
                        else if (tmp == tmp.Parent.Left)
                        {
                            if (tmp2.Right == null)
                            {
                                Node<T> copied = new Node<T>(tmp2.Value, tmp.Parent, tmp.Left, tmp.Right);
                                tmp.Parent.Left = copied;
                                tmp.Left.Parent = copied;
                                tmp.Right.Parent = copied;
                                tmp = null;
                            }
                            else
                            {
                                tmp2.Right.Parent = tmp2.Parent;
                                tmp2.Parent.Left = tmp2.Right;
                                Node<T> copied = new Node<T>(tmp2.Value, tmp.Parent, tmp.Left, tmp.Right);
                                tmp.Parent.Left = copied;
                                tmp.Left.Parent = copied;
                                tmp.Right.Parent = copied;
                                tmp = null;
                            }
                            return  ;
                        }
                        else if(tmp == tmp.Parent.Right)
                        {
                            if (tmp2.Right == null)
                            {
                                Node<T> copied = new Node<T>(tmp2.Value, tmp.Parent, tmp.Left, tmp.Right);
                                tmp.Parent.Right = copied;
                                tmp.Left.Parent = copied;
                                tmp.Right.Parent = copied;
                            }
                            else
                            {
                                tmp2.Right.Parent = tmp2.Parent;
                                tmp2.Parent.Left = tmp2.Right;
                                Node<T> copied = new Node<T>(tmp2.Value, tmp.Parent, tmp.Left, tmp.Right);
                                tmp.Parent.Right = copied;
                                tmp.Left.Parent = copied;
                                tmp.Right.Parent = copied;
                            }
                        }
                        if(tmp2.Right == null)
                        {
                            tmp2.Parent.Left = null;
                        }
                        else
                        {
                            tmp2.Parent.Left = tmp2.Right;
                            tmp2.Right.Parent = tmp2.Parent;
                        }
                        return  ;
                    }
                }
            }
        }

        public int CompareTo(Node<T>? other)
        {
            if (other == null)
            {
                throw new InvalidOperationException("Can't compare with null element");
            }
            if(this.Value.CompareTo(other.Value) > 0)
            {
                return 1;
            }
            else if(this.Value.CompareTo(other.Value) < 0)
            {
                return -1;
            }
            else return 0;
        }
        public bool Equals(Node<T>? other)
        {
            if(other == null)
            {
                return false;
            }
            return this.GetHashCode() == other.GetHashCode();
        }
        public override bool Equals(object obj)
        {
            return Equals(obj as Node<T>);
        }
        public override int GetHashCode()
        {
            return this.Value.GetHashCode();
        }
        public override string ToString()
        {
            if (this.Value == null)
            {
                return "There is no value to use Console.WriteLine() with";
            }
            return this.Value.ToString();
        }
        

        static public bool operator >(Node<T> node1, Node<T> node2)
        {
            return node1.CompareTo(node2) > 0;
        }
        static public bool operator <(Node<T> node1, Node<T> node2)
        {
            return node1.CompareTo(node2) < 0;
        }

        static public bool operator >=(Node<T> node1, Node<T> node2)
        {

            return node1.CompareTo(node2) >= 0 || node1.Equals(node2);
        }
        static public bool operator <=(Node<T> node1, Node<T> node2)
        {
            return node1.CompareTo(node2) <= 0 || node1.Equals(node2);
        }

        static public bool operator ==(Node<T>? node1, Node<T>? node2)
        {
            if (node1 is null && node2 is null)
            {
                return true;
            }
            else if (node1 is null || node2 is null)
            {
                return false;
            }
            return node1.Equals(node2);
        }
        static public bool operator !=(Node<T>? node1, Node<T>? node2)
        {
            if (node1 is null && node2 is null)
            {
                return false;
            }
            else if (node1 is null || node2 is null)
            {
                return true;
            }
            return !node1.Equals(node2);
        }
    }
}
