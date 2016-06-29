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
///////////////////////////////
TEST_FIXTURE(InfoDataFixture,TestIndivs)
{
   using string_type = STRINGTYPE;
    using index_type = INDEXTYPE;
    using data_type = DATATYPE;
   using IndivType = Indiv<index_type,data_type,string_type>;
   for (size_t i = 0; i < nRows; ++i){
     index_type aIndex = (index_type)(i + 1);
     string_type sigle = rowNames[i];
     CHECK(!sigle.empty());
     std::vector<data_type> data(nCols);
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
       CHECK_EQUAL(data[j], pCenter[j]);
     }// j
   }// i
}//TestIndivs
TEST_FIXTURE(InfoDataFixture,TestMatData)
{
   using index_type = INDEXTYPE;
   using data_type = FLOATTYPE;
   using distance_type = DISTANCETYPE;
   using string_type = STRINGTYPE;
		//
   using strings_vector = std::vector<string_type>;
   using DistanceMapType = DistanceMap<index_type, distance_type>;
   using PDistanceMapType = DistanceMapType *;
   using MatDataType = MatData<index_type, data_type, distance_type,string_type>;
   using MatDataPtr = std::shared_ptr<MatDataType>;
   //
   MatDataPtr oPtr = MatDataType::create(nRows,nCols,gdata,&rowNames,&colNames);
   MatDataType *pMat = oPtr.get();
   CHECK(pMat != nullptr);
   CHECK_EQUAL(nRows,pMat->rows());
   CHECK_EQUAL(nCols, pMat->cols());
   for (size_t i = 0; i < nRows; ++i){
     CHECK_EQUAL(rowNames[i], pMat->row_name(i));
     for (size_t j = 0; j < nCols; ++j){
       data_type d = pMat->get_value(i,j);
       CHECK(d >= 0.0);
       CHECK(d <= 1.0);
     }// j
   }// i
   for (size_t i = 0; i < nCols; ++ i){
     CHECK_EQUAL(colNames[i], pMat->col_name(i));
   }// i
   PDistanceMapType pMapRows = pMat->get_rows_distances_map();
   CHECK(pMapRows != nullptr);
   PDistanceMapType pMapCols = pMat->get_cols_distances_map();
   CHECK(pMapCols != nullptr);
}//TestMatData
TEST_FIXTURE(InfoDataFixture,TestMatDataAsync)
{
   using index_type = INDEXTYPE;
   using data_type = FLOATTYPE;
   using distance_type = DISTANCETYPE;
   using string_type = STRINGTYPE;
		//
   using strings_vector = std::vector<string_type>;
   using DistanceMapType = DistanceMap<index_type, distance_type>;
   using PDistanceMapType = DistanceMapType *;
   using MatDataType = MatData<index_type, data_type, distance_type,string_type>;
   using MatDataPtr = std::shared_ptr<MatDataType>;
   //
   std::future<MatDataPtr> oFuture = MatDataType::createAsync(nRows,nCols,gdata,&rowNames,&colNames);
   MatDataPtr oPtr = oFuture.get();
   MatDataType *pMat = oPtr.get();
   CHECK(pMat != nullptr);
   CHECK_EQUAL(nRows,pMat->rows());
   CHECK_EQUAL(nCols, pMat->cols());
   for (size_t i = 0; i < nRows; ++i){
     CHECK_EQUAL(rowNames[i], pMat->row_name(i));
     for (size_t j = 0; j < nCols; ++j){
       data_type d = pMat->get_value(i,j);
       CHECK(d >= 0.0);
       CHECK(d <= 1.0);
     }// j
   }// i
   for (size_t i = 0; i < nCols; ++ i){
     CHECK_EQUAL(colNames[i], pMat->col_name(i));
   }// i
   PDistanceMapType pMapRows = pMat->get_rows_distances_map();
   CHECK(pMapRows != nullptr);
   PDistanceMapType pMapCols = pMat->get_cols_distances_map();
   CHECK(pMapCols != nullptr);
}//TestMatDataAsync