//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// table_page_test.cpp
//
// Identification: test/storage/table_page_test.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <vector>

#include "catalog/column.h"
#include "catalog/schema.h"
#include "gtest/gtest.h"
#include "storage/page/page.h"
#include "storage/page/table_page.h"
#include "storage/table/tuple.h"
#include "type/value_factory.h"

namespace bustub {

// NOLINTNEXTLINE
TEST(TablePageTest, VectorTupleDoesNotUnderflowOffset) {
  Page page;
  auto *table_page = reinterpret_cast<TablePage *>(page.GetData());
  table_page->Init();

  Schema schema{{Column{"v", TypeId::VECTOR, 128}, Column{"id", TypeId::INTEGER}}};
  Tuple tuple{{ValueFactory::GetVectorValue(std::vector<double>(128, 0.0)), ValueFactory::GetIntegerValue(0)}, &schema};

  ASSERT_EQ(tuple.GetLength(), 1036);
  for (uint32_t i = 0; i < 3; i++) {
    ASSERT_TRUE(table_page->InsertTuple({0, false}, tuple).has_value());
  }

  EXPECT_FALSE(table_page->InsertTuple({0, false}, tuple).has_value());
  EXPECT_EQ(table_page->GetNumTuples(), 3);
}

}  // namespace bustub
