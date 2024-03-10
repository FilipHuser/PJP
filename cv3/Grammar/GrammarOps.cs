using Grammar;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;

namespace Lab3
{
	public class GrammarOps
	{
		public GrammarOps(IGrammar g)
		{
			this.g = g;
			compute_empty();
            compute_first();
        }

		public ISet<Nonterminal> EmptyNonterminals { get; } = new HashSet<Nonterminal>(); //NON-TERMINAL = 'A' uppercase

        public ISet<Terminal> First { get; } = new HashSet<Terminal>(); //TERMINAL = 'a' lowercase

        private void compute_empty()
		{
            ///TODO: Add your code here...
            ///
            foreach (var rule in g.Rules)
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

                foreach (var rule in g.Rules)
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

        public string[,] compute_first()
        {
            int t_count = g.Terminals.Count; //number of terminals
            int n_t_count = g.Nonterminals.Count; //number of non-terminals

            string[,] s_u_t = new string[t_count, t_count + n_t_count]; //sets union table

            List<Symbol> symbols = new List<Symbol>();

            symbols.AddRange(g.Nonterminals); symbols.AddRange(g.Terminals);



            Dictionary<string, int> nonterminal_indexes = new Dictionary<string, int>();
            Dictionary<string, int> symbol_indexes = new Dictionary<string, int>();

            for(int i = 0; i < g.Nonterminals.Count; i++)
            {
                nonterminal_indexes[g.Nonterminals[i].Name] = i;
            }

            for (int i = 0; i < symbols.Count; i++)
            {
                symbol_indexes[symbols[i].Name] = i;
            }

            foreach (var rule in g.Rules)
            {
                if (rule.RHS.Count == 0) { s_u_t[nonterminal_indexes[rule.LHS.Name], symbol_indexes[rule.LHS.Name]] = "*";  } 

                foreach(var symbol in rule.RHS)
                {
                    if(symbol is Terminal || !EmptyNonterminals.Contains(symbol))
                    {
                        s_u_t[nonterminal_indexes[rule.LHS.Name], symbol_indexes[symbol.Name]] = "*";
                        break;
                    }

                    if (symbol is Nonterminal && EmptyNonterminals.Contains(symbol))
                    {
                        s_u_t[nonterminal_indexes[rule.LHS.Name], symbol_indexes[symbol.Name]] = "*";
                    }
                }
            }

            bool changed = false;
            string[,] tmp_s_u_t = new string[n_t_count, symbols.Count];

            for (int i = 0; i < n_t_count; i++)
            {
                if (i == n_t_count - 1 && changed) { i = 0; changed = false; }
                for (int j = 0; j < n_t_count; j++)
                {

                    if (s_u_t[i, j] == "*")
                    {
                       Array.Copy(s_u_t, tmp_s_u_t, s_u_t.Length);

                       for (int k = 0; k < symbols.Count; k++)
                       {
                            if (s_u_t[i , k] != "*")
                            {
                                s_u_t[i, k] = s_u_t[j, k];
                            }
                       }

                       if (!ArraysEqual(s_u_t, tmp_s_u_t)) { changed = true; }

                    }
                }
            }

            Console.WriteLine("--------------------------- FIRST ---------------------------");

            foreach (var rule in g.Rules)
            {
                // Create a new StringBuilder instance for each iteration
                StringBuilder sb = new StringBuilder("first[{0}:{1}] = {2}");

                sb.Replace("{0}", rule.LHS.Name);
                string r = "";
                foreach (var s in rule.RHS)
                {
                    r += s.Name;
                }

                List<string> output = new List<string>();

                if (rule.RHS.Count == 0) { output.Clear(); }

                foreach (var s in rule.RHS)
                {
                    if (s is Terminal || !EmptyNonterminals.Contains(s))
                    {
                        if (!output.Contains(s.Name))
                        {
                            output.Add(s.Name);
                        }
                        break;

                    }

                    for (int i = g.Nonterminals.Count; i < symbols.Count; i++)
                    {
                        if (s_u_t[nonterminal_indexes[rule.LHS.Name], i] == "*")
                        {
                            if (!output.Contains(symbols[i].Name))
                            {
                                output.Add(symbols[i].Name);
                            }
                        }
                    }
                }

                sb.Replace("{1}", r);
                sb.Replace("{2}", string.Join(" ", output));

                Console.WriteLine(sb.ToString());
                output.Clear();
            }

            Console.WriteLine("-------------------------------------------------------------");

            return s_u_t;

        }

        public void print_table(string[,] table_2D)
        {
            int rows = table_2D.GetLength(0);
            int cols = table_2D.GetLength(1);

            List<Symbol> symbols = new List<Symbol>();

            symbols.AddRange(g.Nonterminals);
            symbols.AddRange(g.Terminals);

            Console.Write("  ");

            foreach (var s in symbols)
            {
                Console.Write(s.Name + " ");
            }

            Console.WriteLine(" ");

            for(int i = 0; i < rows; i++)
            {
                Console.Write(g.Nonterminals[i].Name);

                for(int j = 0; j < cols; j++)
                {
                    if (j == 0) { Console.Write(" "); }

                    if(table_2D[i , j] == "*")
                    {
                        Console.Write("* ");

                    } else {

                        Console.Write("  ");
                    }
                }
                Console.WriteLine();
            }

        }

        private bool ArraysEqual(string[,] arr1, string[,] arr2)
        {
            for (int i = 0; i < arr1.GetLength(0); i++)
            {
                for (int j = 0; j < arr1.GetLength(1); j++)
                {
                    if (arr1[i, j] != arr2[i, j])
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        private IGrammar g; 
	}
}
