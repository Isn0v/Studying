using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CarGame
{
    internal class SportCar : BaseCar
    {
        private const int minimalSpeed = 70;
        private const int maximalSpeed = 150;
        private int wayPassed = 0;

        public override string Name { get; set; }
        public override int Speed { get; set; }
        public override int MaximalSpeed => maximalSpeed;
        public override int MinimalSpeed => minimalSpeed;
        public override int WayPassed {
            get => wayPassed; 
            set => wayPassed = value;
        }
        
        public SportCar(string name) : base(name) { }

        

        public override string ToString()
        {
            return $"SportCar: {Name}";
        }
    }
}
