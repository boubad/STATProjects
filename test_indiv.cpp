//test_indiv.cpp
#include <unittest++/UnitTest++.h>
////////////////////////////
#include <indiv.h>
#include <matdata.h>
#include <matelem.h>
#include <treeelem.h>
////////////////////////////////
#include "infodatafixture.h"
#include "global_defs.h"
////////////////////////////
using namespace info;
///////////////////////////
using index_type = INDEXTYPE;
using data_type = FLOATTYPE;
using distance_type = DISTANCETYPE;
using float_type = FLOATTYPE;
using criteria_type = CRITERIATYPE;
using string_type = STRINGTYPE;
using IndivType = Indiv<index_type,data_type,string_type>;
using strings_vector = std::vector<string_type>;
using DistanceMapType = DistanceMap<index_type, distance_type>;
using PDistanceMapType = DistanceMapType *;
using MatDataType = MatData<index_type,float_type, distance_type,string_type>;
using MatDataPtr = std::shared_ptr<MatDataType>;
using matelemresult_type = MatElemResult<index_type,criteria_type>;
using matelemresult_type_ptr = std::shared_ptr<matelemresult_type>;
using matelem_type = MatElem<index_type,distance_type,criteria_type>;
using matord_type = MatOrd<index_type,distance_type,criteria_type>;
using matordresult_type = std::pair<matelemresult_type_ptr,matelemresult_type_ptr>;
///////////////////////////////
TEST_FIXTURE(InfoDataFixture,TestIndivs)
{
   for (size_t i = 0; i < nRows; ++i){
     index_type aIndex = (index_type)(i + 1);
     string_type sigle = rowNames[i];
     CHECK(!sigle.empty());
     std::vector<int> data(nCols);
     for (size_t j = 0; j < nCols; ++j){
       data[j] = gdata[i*nCols + j];
     }// j
     IndivType oIndiv(aIndex,nCols,data,sigle);
     CHECK_EQUAL(aIndex, oIndiv.id());
     CHECK_EQUAL(sigle, oIndiv.sigle());
     CHECK_EQUAL(nCols, oIndiv.size());
     const data_type *pCenter = oIndiv.center();
     CHECK(pCenter != nullptr);
     for (size_t j = 0; j < nCols; ++j){
       CHECK_EQUAL((data_type)data[j], pCenter[j]);
     }// j
   }// i
}//TestIndivs
TEST_FIXTURE(InfoDataFixture,TestMatData)
{
   MatDataPtr oPtr = MatDataType::create(nRows,nCols,gdata,&rowNames,&colNames);
   MatDataType *pMat = oPtr.get();
   CHECK(pMat != nullptr);
   CHECK(pMat->is_valid());
   CHECK_EQUAL(nRows,pMat->rows());
   CHECK_EQUAL(nCols, pMat->cols());
   for (size_t i = 0; i < nRows; ++i){
     CHECK_EQUAL(rowNames[i], pMat->get_row_name(i));
     for (size_t j = 0; j < nCols; ++j){
       float_type d = pMat->get_data(i,j);
       CHECK(d >= 0.0);
       CHECK(d <= 1.0);
     }// j
   }// i
   for (size_t i = 0; i < nCols; ++ i){
     CHECK_EQUAL(colNames[i], pMat->get_col_name(i));
   }// i
   PDistanceMapType pMapRows = pMat->get_rows_distances_map();
   CHECK(pMapRows != nullptr);
   PDistanceMapType pMapCols = pMat->get_cols_distances_map();
   CHECK(pMapCols != nullptr);
}//TestMatData
TEST_FIXTURE(InfoDataFixture,TestMatElem)
{
   MatDataPtr oPtr = MatDataType::create(nRows,nCols,gdata,&rowNames,&colNames);
   MatDataType *pMat = oPtr.get();
   CHECK(pMat != nullptr);
   CHECK(pMat->is_valid());
   matelemresult_type_ptr r = matelem_type::st_arrange_hierar(pMat);
   matelemresult_type *p = r.get();
   CHECK(p != nullptr);
   std::cout << std::endl ;
   p->write_to(std::cout);
   std::cout << std::endl;
}//TestMatElem
TEST_FIXTURE(InfoDataFixture,TestMatOrd)
{
   MatDataPtr oPtr = MatDataType::create(nRows,nCols,gdata,&rowNames,&colNames);
   MatDataType *pMat = oPtr.get();
   CHECK(pMat != nullptr);
   CHECK(pMat->is_valid());
   matordresult_type r = matord_type::st_arrange_all_hierar(pMat);
   matelemresult_type *p = r.first.get();
   CHECK(p != nullptr);
   std::cout << std::endl << *p;
    matelemresult_type *pp = r.second.get();
   CHECK(pp != nullptr);
   std::cout << std::endl << *pp;
   std::cout << std::endl;
}//TestMatOrd

