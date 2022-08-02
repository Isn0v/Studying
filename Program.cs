namespace BST
{
    internal class Program
    {
        static void Main(string[] args)
        {
            BST<int> bst = new BST<int>(5);
            bst.Add(10);
            bst.Add(4);
            bst.RecursiveAdd(20);
            bst.Add(2);
            bst.Add(3);
            bst.Add(6);
            bst.Add(8);
            bst.Add(11);
            //Console.WriteLine(bst.Contains(2));
            Console.WriteLine(bst);
            bst.Remove(25);
            Console.WriteLine(bst);
        }
    }
}