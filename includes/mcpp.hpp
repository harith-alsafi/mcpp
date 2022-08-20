#pragma once

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

#include "mathematic/mathematic.hpp"
#include "numerical/vect.hpp"

#include "variables/others.hpp"
#include "variables/table.hpp"
#include "variables/matrix.hpp"
#include "variables/point.hpp"
#include "variables/tree.hpp"
#include "variables/vecop.hpp"

#include "algebra/solvers.hpp"

#include "numerical/linear.hpp"
#include "statistics/stat.hpp"

#include "calculus/differential.hpp"
#include "calculus/integral.hpp"
#include "communication/signals.hpp"