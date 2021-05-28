#ifndef CHARSAMPLES_H
#define CHARSAMPLES_H

#include <vector>

static std::vector<std::vector<bool>> Number0 () {
  return {{1,1,1},
          {1,0,1},
          {1,0,1},
          {1,0,1},
          {1,1,1}};
}

static std::vector<std::vector<bool>> Number1 () {
  return {{0,0,1},
          {0,0,1},
          {0,0,1},
          {0,0,1},
          {0,0,1}};
}

static std::vector<std::vector<bool>> Number2 () {
  return {{1,1,1},
          {0,0,1},
          {1,1,1},
          {1,0,0},
          {1,1,1}};
}

static std::vector<std::vector<bool>> Number3 () {
  return {{1,1,1},
          {0,0,1},
          {0,1,1},
          {0,0,1},
          {1,1,1}};
}

static std::vector<std::vector<bool>> Number4 () {
  return {{1,0,1},
          {1,0,1},
          {1,1,1},
          {0,0,1},
          {0,0,1}};
}

static std::vector<std::vector<bool>> Number5 () {
  return {{1,1,1},
          {1,0,0},
          {1,1,1},
          {0,0,1},
          {1,1,1}};
}

static std::vector<std::vector<bool>> Number6 () {
  return {{1,1,1},
          {1,0,0},
          {1,1,1},
          {1,0,1},
          {1,1,1}};
}

static std::vector<std::vector<bool>> Number7 () {
  return {{1,1,1},
          {0,0,1},
          {0,0,1},
          {0,0,1},
          {0,0,1}};
}

static std::vector<std::vector<bool>> Number8 () {
  return {{1,1,1},
          {1,0,1},
          {1,1,1},
          {1,0,1},
          {1,1,1}};
}

static std::vector<std::vector<bool>> Number9 () {
  return {{1,1,1},
          {1,0,1},
          {1,1,1},
          {0,0,1},
          {1,1,1}};
}

static std::vector<std::vector<bool>> Score () {
  return {{1,1,1, 0 ,1,1,1, 0 ,1,1,1, 0 ,1,1,1, 0 ,1,1,1,},
          {1,0,0, 0 ,1,0,0, 0 ,1,0,1, 0 ,1,0,1, 0 ,1,0,0,},
          {1,1,1, 0 ,1,0,0, 0 ,1,0,1, 0 ,1,1,0, 0 ,1,1,0,},
          {0,0,1, 0 ,1,0,0, 0 ,1,0,1, 0 ,1,0,1, 0 ,1,0,0,},
          {1,1,1, 0 ,1,1,1, 0 ,1,1,1, 0 ,1,0,1, 0 ,1,1,1,}};
}

static std::vector<std::vector<bool>> Best () {
  return {{1,1,1, 0 ,1,1,1, 0 ,1,1,1, 0 ,1,1,1,},
          {1,0,1, 0 ,1,0,0, 0 ,1,0,0, 0 ,0,1,0,},
          {1,1,0, 0 ,1,1,0, 0 ,1,1,1, 0 ,0,1,0,},
          {1,0,1, 0 ,1,0,0, 0 ,0,0,1, 0 ,0,1,0,},
          {1,1,1, 0 ,1,1,1, 0 ,1,1,1, 0 ,0,1,0,}};
}

static std::vector<std::vector<bool>> Anaconda () {
  return {{1, 1, 1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1, 1},
          {1, 0, 0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0, 1},
          {1, 0, 1,1,1,1, 0 ,1,0,0,1, 0 ,1,1,1,1, 0 ,1,1,1,1, 0 ,1,1,1,1, 0 ,1,0,0,1, 0 ,1,1,1,0, 0 ,1,1,1,1, 0, 1},
          {1, 0, 1,0,0,1, 0 ,1,1,0,1, 0 ,1,0,0,1, 0 ,1,0,0,0, 0 ,1,0,0,1, 0 ,1,1,0,1, 0 ,1,0,0,1, 0 ,1,0,0,1, 0, 1},
          {1, 0, 1,1,1,1, 0 ,1,0,1,1, 0 ,1,1,1,1, 0 ,1,0,0,0, 0 ,1,0,0,1, 0 ,1,0,1,1, 0 ,1,0,0,1, 0 ,1,1,1,1, 0, 1},
          {1, 0, 1,0,0,1, 0 ,1,0,0,1, 0 ,1,0,0,1, 0 ,1,0,0,0, 0 ,1,0,0,1, 0 ,1,0,0,1, 0 ,1,0,0,1, 0 ,1,0,0,1, 0, 1},
          {1, 0, 1,0,0,1, 0 ,1,0,0,1, 0 ,1,0,0,1, 0 ,1,1,1,1, 0 ,1,1,1,1, 0 ,1,0,0,1, 0 ,1,1,1,0, 0 ,1,0,0,1, 0, 1},
          {1, 0, 0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0 ,0,0,0,0, 0, 1},
          {1, 1, 1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1 ,1,1,1,1, 1, 1}};
}

static std::vector<std::vector<bool>> TwoDots () {
  return {{0,0},
          {1,0},
          {0,0},
          {1,0},
          {0,0}};
}

static std::vector<std::vector<bool>> GridFromNumber(int num) {

  switch (num) {
    case 0:
      return Number0();
      break;
    case 1:
      return Number1();
      break;
    case 2:
      return Number2();
      break;
    case 3:
      return Number3();
      break;
    case 4:
      return Number4();
      break;
    case 5:
      return Number5();
      break;
    case 6:
      return Number6();
      break;
    case 7:
      return Number7();
      break;
    case 8:
      return Number8();
      break;
    case 9:
      return Number9();
      break;
    default:
      return {};
      break;
  }

}


#endif