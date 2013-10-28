/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* fermin at tid dot es
*
* Author: Ken Zangelin
*/
#include <stdio.h>
#include <string>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "common/tag.h"
#include "ngsi/ContextRegistrationVector.h"



/* ****************************************************************************
*
* ContextRegistrationVector::push_back - 
*/
void ContextRegistrationVector::push_back(ContextRegistration* item)
{
  vec.push_back(item);
}



/* ****************************************************************************
*
* ContextRegistrationVector::render - 
*/
std::string ContextRegistrationVector::render(Format format, std::string indent)
{
  std::string  out = "";
  std::string  tag = "contextRegistrationList";

  if (vec.size() == 0)
    return "";

  out += startTag(indent, tag, format);

  for (unsigned int ix = 0; ix < vec.size(); ++ix)
    out += vec[ix]->render(format, indent + "  ");

  out += endTag(indent, tag, format);

  return out;
}



/* ****************************************************************************
*
* ContextRegistrationVector::present - 
*/
void ContextRegistrationVector::present(std::string indent)
{
   PRINTF("%lu ContextRegistrations", (unsigned long) vec.size());

   for (unsigned int ix = 0; ix < vec.size(); ++ix)
      vec[ix]->present(indent, ix);
}



/* ****************************************************************************
*
* ContextRegistrationVector::release - 
*/
void ContextRegistrationVector::release(void)
{
  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
     vec[ix]->release();
     delete(vec[ix]);
  }

  vec.clear();
}



/* ****************************************************************************
*
* ContextRegistrationVector::get - 
*/
ContextRegistration* ContextRegistrationVector::get(int ix)
{
  return vec[ix];
}



/* ****************************************************************************
*
* ContextRegistrationVector::size - 
*/
unsigned int ContextRegistrationVector::size(void)
{
  return vec.size();
}



/* ****************************************************************************
*
* ContextRegistrationVector::check - 
*/
std::string ContextRegistrationVector::check(RequestType requestType, Format format, std::string indent, std::string predetectedError, int counter)
{
  for (unsigned int ix = 0; ix < vec.size(); ++ix)
  {
     std::string res;

     if ((res = vec[ix]->check(requestType, format, indent, predetectedError, counter)) != "OK")
       return res;
  }

  return "OK";
}