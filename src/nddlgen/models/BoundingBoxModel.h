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

#ifndef NDDLGEN_MODELS_BOUNDINGBOXMODEL_H_
#define NDDLGEN_MODELS_BOUNDINGBOXMODEL_H_

#include <boost/shared_ptr.hpp>

namespace nddlgen
{
	namespace models
	{
		class BoundingBoxModel;
		typedef boost::shared_ptr<nddlgen::models::BoundingBoxModel> BoundingBoxModelPtr;
	}
}

class nddlgen::models::BoundingBoxModel
{

	private:

		int _plusX;
		int _minusX;
		int _plusY;
		int _minusY;
		int _plusZ;
		int _minusZ;

	public:

		BoundingBoxModel();
		BoundingBoxModel(int plusX, int minusX, int plusY, int minusY, int plusZ, int minusZ);
		virtual ~BoundingBoxModel();

		int getPlusX();
		void setPlusX(int plusX);
		int getMinusX();
		void setMinusX(int minusX);
		int getPlusY();
		void setPlusY(int plusY);
		int getMinusY();
		void setMinusY(int minusY);
		int getPlusZ();
		void setPlusZ(int plusZ);
		int getMinusZ();
		void setMinusZ(int minusZ);

};

#endif
