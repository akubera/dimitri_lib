// Copyright 2013 Michael Lopez
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.



#include <iostream>
#include "parser.hpp"
#include "../../congruence/congruence.hpp"


using namespace std;

void print_test_funcs (expr* e1, expr* e2)
{
  cout << "args:\n";
  for (auto e : Args()(e1))
    cout << "  " << e << '\n';
  cout << e1 << (Is_same()(e1,e2) ? "=" : "/=") << e2 << '\n';
  cout << "num args: " << Num_args()(e1) << '\n';
}

using congruence_t = dimitri::congruence_t<expr*, Args, Is_same, Num_args>;



int main ()
{
  parser_t parser;
  auto fa = parser.parse("f(a)");
  auto ffa = parser.parse("f(f(a))");
  auto ffffa = parser.parse("f(f(f(f(a))))");
  auto fga = parser.parse("f(g(a))");
  auto gb = parser.parse("g(b)");

  congruence_t eq;
  eq.set_congruent(fa,ffa);

  std::cout << "(fa == ffa) = " << (eq.is_congruent(fa, ffa) ? "true" : "false") << "\n";
  std::cout << "(fa == ffffa) = " << (eq.is_congruent(fa, ffffa) ? "true" : "false") << "\n";
  std::cout << "(ffa == ffffa) = " << (eq.is_congruent(ffa, ffffa) ? "true" : "false") << "\n";
  std::cout << "(fa == fga) = " << (eq.is_congruent(fa, fga) ? "true" : "false") << "\n";
  std::cout << "(fa == gb) = " << (eq.is_congruent(fa, gb) ? "true" : "false") << "\n";
  
  return 0;
}