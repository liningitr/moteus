// Copyright 2018 Josh Pieper, jjp@pobox.com.  All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "moteus/foc.h"

#include <boost/test/auto_unit_test.hpp>

using namespace moteus;

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_CASE(FocTest1) {
  SinCos sin_cos(0.0);

  DqTransform dq(sin_cos, 2.0, 0., 0.);
  BOOST_TEST(dq.d == 1.3333333333f);
  BOOST_TEST(dq.q == 0.0);

  ClarkTransform ct(2.0, 0., 0.);
  BOOST_TEST(ct.x == 1.3333333333f);
  BOOST_TEST(ct.y == 0.0);

  ParkTransform pt(sin_cos, ct.x, ct.y);
  BOOST_TEST(pt.d == dq.d);
  BOOST_TEST(pt.q == dq.q);
}

BOOST_AUTO_TEST_CASE(FocTest2) {
  SinCos sin_cos(kPi / 2.0);

  DqTransform dq(sin_cos, 2.0, 0., 0.);
  BOOST_TEST(std::abs(dq.d) <= 1e-5);
  BOOST_TEST(dq.q == -1.33333333333f);

  ClarkTransform ct(2.0, 0., 0.);
  BOOST_TEST(ct.x == 1.333333333333f);
  BOOST_TEST(ct.y == 0.0f);

  ParkTransform pt(sin_cos, ct.x, ct.y);
  BOOST_TEST(pt.d == dq.d);
  BOOST_TEST(pt.q == dq.q);
}
