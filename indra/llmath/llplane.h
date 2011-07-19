/** 
 * @file llplane.h
 *
 * $LicenseInfo:firstyear=2001&license=viewergpl$
 * 
 * Copyright (c) 2001-2009, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlifegrid.net/programs/open_source/licensing/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#ifndef LL_LLPLANE_H
#define LL_LLPLANE_H

#include "v3math.h"
#include "v4math.h"

// A simple way to specify a plane is to give its normal,
// and it's nearest approach to the origin.
// 
// Given the equation for a plane : A*x + B*y + C*z + D = 0
// The plane normal = [A, B, C]
// The closest approach = D / sqrt(A*A + B*B + C*C)

class LLPlane
{
public:
	
	// Constructors
	LLPlane() {}; // no default constructor
	LLPlane(const LLVector3 &p0, F32 d) { setVec(p0, d); }
	LLPlane(const LLVector3 &p0, const LLVector3 &n) { setVec(p0, n); }
	inline void setVec(const LLVector3 &p0, F32 d) { mV.set(p0[0], p0[1], p0[2], d); }
	
	// Set
	inline void setVec(const LLVector3 &p0, const LLVector3 &n)
	{
		F32 d = -(p0 * n);
		setVec(n, d);
	}
	inline void setVec(const LLVector3 &p0, const LLVector3 &p1, const LLVector3 &p2)
	{
		LLVector3 u, v, w;
		u = p1 - p0;
		v = p2 - p0;
		w = u % v;
		w.normVec();
		F32 d = -(w * p0);
		setVec(w, d);
	}
	
	inline LLPlane& operator=(const LLVector4& v2) {  mV.set(v2[0],v2[1],v2[2],v2[3]); return *this;}
	
	inline LLPlane& operator=(const LLVector4a& v2) {  mV.set(v2[0],v2[1],v2[2],v2[3]); return *this;}	
	
	inline void set(const LLPlane& p2) { mV = p2.mV; }
	
	// 
	F32 dist(const LLVector3 &v2) const { return mV[0]*v2[0] + mV[1]*v2[1] + mV[2]*v2[2] + mV[3]; }
	
	inline LLSimdScalar dot3(const LLVector4a& b) const { return mV.dot3(b); }
	
	// Read-only access a single float in this vector. Do not use in proximity to any function call that manipulates
	// the data at the whole vector level or you will incur a substantial penalty. Consider using the splat functions instead	
	inline F32 operator[](const S32 idx) const { return mV[idx]; }
	
	// preferable when index is known at compile time
	template <int N> LL_FORCE_INLINE void getAt(LLSimdScalar& v) const { v = mV.getScalarAt<N>(); } 
	
	// reset the vector to 0, 0, 0, 1
	inline void clear() { mV.set(0, 0, 0, 1); }
	
	inline void getVector3(LLVector3& vec) const { vec.set(mV[0], mV[1], mV[2]); }
	
	// Retrieve the mask indicating which of the x, y, or z axis are greater or equal to zero.
	inline U8 calcPlaneMask() 
	{ 
		return mV.greaterEqual(LLVector4a::getZero()).getGatheredBits() & LLVector4Logical::MASK_XYZ;
	}
		
private:
	LLVector4a mV;
};



#endif // LL_LLPLANE_H
