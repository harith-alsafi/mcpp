#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <numeric>
#include <limits>
#include <cmath>

// foward declarations 
namespace var
{
	template <typename D>
	class matrix;
}

namespace lalg
{
	template <typename D>
	var::matrix<D> eye(int n);

	template <typename D>
	var::matrix<D> perms(D a, D b);
}

#include "variables/vecop.hpp"
#include "variables/table.hpp"
#include "numerical/vect.hpp"
#include "variables/matrix.hpp"
#include "variables/tree.hpp"
#include "variables/point.hpp"

#include "mathematic/mathematic.hpp"
#include "algebra/solvers.hpp"

#include "statistics/stat.hpp"
#include "numerical/linear.hpp"

#include "communication/signals.hpp"
#include "calculus/differential.hpp"
#include "calculus/integral.hpp"