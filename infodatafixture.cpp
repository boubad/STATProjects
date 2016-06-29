/*
 * Copyright 2016 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include "infodatafixture.h"
#include "infotestdata.h"
////////////////////////////
using namespace info;
///////////////////////////
InfoDataFixture::InfoDataFixture():nRows(0),nCols(0)
{
  InfoTestData::get_mortal_data(name,nRows,nCols,gdata,rowNames,colNames);
}

InfoDataFixture::~InfoDataFixture()
{

}
