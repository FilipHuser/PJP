using Grammar;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab3
{
	public class GrammarOps
	{
		public GrammarOps(IGrammar g)
		{
			this.g = g;
			compute_empty(); 
		}

		public ISet<Nonterminal> EmptyNonterminals { get; } = new HashSet<Nonterminal>(); //NON-TERMINAL = 'A' uppercase

		private void compute_empty()
		{
            ///TODO: Add your code here...
            ///

            foreach (Rule rule in g.Rules)
            {
                if (rule.RHS.Count == 0)
                {
                    EmptyNonterminals.Add(rule.LHS);
                }
            }

            bool changed = true;

            while (changed)
            {
                changed = false;

                foreach (Rule rule in g.Rules)
                {
                    if (!EmptyNonterminals.Contains(rule.LHS))
                    {
                        // Pokud všechny symboly na pravé straně jsou v nullableSet
                        if (rule.RHS.All(symbol => symbol is Terminal || EmptyNonterminals.Contains((Nonterminal)symbol)))
                        {
                            EmptyNonterminals.Add(rule.LHS);
                            changed = true;
                        }
                    }
                }
            }
        }

		private IGrammar g; 
	}
}
