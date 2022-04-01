#pragma once

#include <gui/mainwindow.h>

#include <QApplication>
#include <iostream>

#include <generic/types.h>
#include <generic/vec_ops.h>
#include <generic/serialize.h>
#include <generic/test_data.h>

#include <ranges>

#include <database/text.h>

#include <generic/print.h>



int main(int argc, char *argv[])
{
    TestData test_data;
//    auto txts = test_data.texts_.get_txts(
//                test_data.texts_.get_indexes(TextsViewFilter::None));
//    print_table(test_data.texts_.txt_);

//    vector<uint8> vec2{3, 0, 1, 2, 6, 5, 2, 3, 0};
//    vector<f32> vec2{9843.23f, 1.f, 2325.f, 3.f};
//    sort_vecs(vec1, vec2, vec3);

////    std::ranges::sort(vec2);
//    auto index_diff = map_vector_index_dif(vec1, vec2);

//    print_table pr3(vec1, vec2);
//    print_table diff(index_diff.old_idx, index_diff.new_idx);

//    QApplication a(argc, argv);
//    MainWindow w(nullptr, &test_data.texts_);
//    w.show();
//    return a.exec();
}
