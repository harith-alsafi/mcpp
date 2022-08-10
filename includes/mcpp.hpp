#pragma once
#include <algorithm>
#include <cmath>
#include <complex>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <vector>

// foward declarations
namespace var
{
	template <typename D>
	class table;
	template <typename D>
	class matrix;
	template <typename D>
	class point;
	template <typename D>
	class tree;
}

namespace lalg
{
	template <typename D>
	var::matrix<D> eye(int n);
	template <typename D>
	var::matrix<D> perms(D a, D b);
}

#include "numerical/vect.hpp"
#include "variables/matrix.hpp"
#include "variables/point.hpp"
#include "variables/table.hpp"
#include "variables/tree.hpp"
#include "variables/vecop.hpp"

#include "mathematic/mathematic.hpp"
#include "algebra/solvers.hpp"

#include "numerical/linear.hpp"
#include "statistics/stat.hpp"

#include "calculus/differential.hpp"
#include "calculus/integral.hpp"
#include "communication/signals.hpp"