using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CarGame
{

    internal abstract class BaseCar
    {
        public abstract string Name { get; set; }
        public abstract int Speed { get; set; }
        public abstract int MaximalSpeed { get; }
        public abstract int MinimalSpeed { get; }
        public abstract int WayPassed { get; set; }

        public BaseCar(string name)
        {
            Name = name;
        }

        public void Drive(Random r)
        {
            Speed = r.Next(MinimalSpeed, MaximalSpeed + 1);
            WayPassed += Speed;
        }

        public bool isFinished(int fullWay)
        {
            return WayPassed >= fullWay;
        }

        public static void finishEvent(BaseCar car)
        {
            Console.WriteLine($"\n{car.Name} finished");
        }

        public void State()
        {
            Console.WriteLine($"{Name} passed {WayPassed} km");
        }
    }

    class CarGameException : ApplicationException { }

    
}
