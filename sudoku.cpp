#include <array>
#include <iostream>
#include <boost/range/irange.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/iterator/filter_iterator.hpp>

using namespace boost::algorithm;

typedef std::array<char, 81> game_t;

bool neighbour(int i, int j) {
  static auto box = [] (int n) { return n / 27 * 3 + n % 9 / 3; };
  static auto row = [] (int n) { return n / 9; };
  static auto col = [] (int n) { return n % 9; };
  return (i != j) && (box(i) == box(j) || row(i) == row(j) || col(i) == col(j));
}

bool taken(const game_t& game, int index, char number) {
  return any_of(boost::irange(0, 81), [&] (int i) { 
    return game[i] == number && neighbour(index, i);
  });
}

bool solve(game_t& game, int index = 0) {
  return any_of(boost::irange('1', ':'), [&] (char number) {
    char f = game[index];
    if (f != '_' && f != number) return false;
    if (taken(game, index, number)) return false;
    
    game[index] = number;
    if (index == 80 || solve(game, index + 1)) return true;
    
    game[index] = f;
    return false;
  });
}

void read(game_t& game) {
  auto valid = boost::make_filter_iterator([] (char c) {
    return (c >= '1' && c <= '9') || c == '_';
  }, std::istream_iterator<char>(std::cin));

  copy_n(valid, 81, game.begin());
}

int main() {
  game_t game;
  read(game);
  solve(game);

  for (auto it = game.begin(); it != game.end(); it += 9) {
    copy_n(it, 9, std::ostream_iterator<char>(std::cout, " "));
    std::cout << std::endl;
  } 
}
