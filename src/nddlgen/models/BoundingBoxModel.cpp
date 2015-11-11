/**
 * Copyright 2015 Christian Dreher (dreher@charlydelta.org)
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
 */

#include <nddlgen/models/BoundingBoxModel.h>

nddlgen::models::BoundingBoxModel::BoundingBoxModel()
{
	this->_plusX = 0;
	this->_minusX = 0;
	this->_plusY = 0;
	this->_minusY = 0;
	this->_plusZ = 0;
	this->_minusZ = 0;
}

nddlgen::models::BoundingBoxModel::BoundingBoxModel(int plusX, int minusX, int plusY, int minusY, int plusZ, int minusZ)
{
	this->_plusX = plusX;
	this->_minusX = minusX;
	this->_plusY = plusY;
	this->_minusY = minusY;
	this->_plusZ = plusZ;
	this->_minusZ = minusZ;
}

nddlgen::models::BoundingBoxModel::~BoundingBoxModel()
{

}

int nddlgen::models::BoundingBoxModel::getPlusX()
{
	return this->_plusX;
}

void nddlgen::models::BoundingBoxModel::setPlusX(int plusX)
{
	this->_plusX = plusX;
}

int nddlgen::models::BoundingBoxModel::getMinusX()
{
	return this->_minusX;
}

void nddlgen::models::BoundingBoxModel::setMinusX(int minusX)
{
	this->_minusX = minusX;
}

int nddlgen::models::BoundingBoxModel::getPlusY()
{
	return this->_plusY;
}

void nddlgen::models::BoundingBoxModel::setPlusY(int plusY)
{
	this->_plusY = plusY;
}

int nddlgen::models::BoundingBoxModel::getMinusY()
{
	return this->_minusY;
}

void nddlgen::models::BoundingBoxModel::setMinusY(int minusY)
{
	this->_minusY = minusY;
}

int nddlgen::models::BoundingBoxModel::getPlusZ()
{
	return this->_plusZ;
}

void nddlgen::models::BoundingBoxModel::setPlusZ(int plusZ)
{
	this->_plusZ = plusZ;
}

int nddlgen::models::BoundingBoxModel::getMinusZ()
{
	return this->_minusZ;
}

void nddlgen::models::BoundingBoxModel::setMinusZ(int minusZ)
{
	this->_minusZ = minusZ;
}
