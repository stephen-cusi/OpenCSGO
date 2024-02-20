//================ Copyright (c) Valve Corporation. All Rights Reserved. =================
//
// d3dxmath.cpp
//
//==================================================================================================

#include "togl/rendermechanism.h"
#include "tier0/dynfunction.h"
#include "tier0/vprof_telemetry.h"
#include "tier0/dbg.h"
#include "tier0/threadtools.h"
#include "tier0/vprof.h"
#include "tier1/strtools.h"
#include "tier1/utlbuffer.h"
#include "mathlib/vmatrix.h"
#include "materialsystem/IShader.h"

#include "tier0/icommandline.h"
#include "tier0/memdbgon.h"

// ------------------------------------------------------------------------------------------------------------------------------ //

D3DXMATRIX D3DXMATRIX::operator*( const D3DXMATRIX &o ) const
{
	D3DXMATRIX result;
	
	D3DXMatrixMultiply( &result, this, &o );	// this = lhs    o = rhs    result = this * o

	return result;
}

D3DXMATRIX::operator FLOAT* ()
{
	return (float*)this;
}

float& D3DXMATRIX::operator()( int row, int column )
{
	return m[row][column];
}

const float& D3DXMATRIX::operator()( int row, int column ) const
{
	return m[row][column];
}

bool D3DXMATRIX::operator != ( CONST D3DXMATRIX& src ) const 
{
 	return V_memcmp( (void*)this, (void*)&src, sizeof(this) ) != 0;
}

// ------------------------------------------------------------------------------------------------------------------------------ //

float& D3DXPLANE::operator[]( int i )
{
	return ((float*)this)[i];
}

bool D3DXPLANE::operator==( const D3DXPLANE &o )
{
	return a == o.a && b == o.b && c == o.c && d == o.d;
}

bool D3DXPLANE::operator!=( const D3DXPLANE &o )
{
	return !( *this == o );
}

D3DXPLANE::operator float*()
{
	return (float*)this;
}

D3DXPLANE::operator const float*() const
{
	return (const float*)this;
}

// ------------------------------------------------------------------------------------------------------------------------------ //

D3DXVECTOR2::operator FLOAT* ()
{
	return (float*)this;
}

D3DXVECTOR2::operator CONST FLOAT* () const
{
	return (const float*)this;
}

// ------------------------------------------------------------------------------------------------------------------------------ //

D3DXVECTOR3::D3DXVECTOR3( float a, float b, float c )
{
	x = a;
	y = b;
	z = c;
}

D3DXVECTOR3::operator FLOAT* ()
{
	return (float*)this;
}

D3DXVECTOR3::operator CONST FLOAT* () const
{
	return (const float*)this;
}

// ------------------------------------------------------------------------------------------------------------------------------ //

D3DXVECTOR4::D3DXVECTOR4( float a, float b, float c, float d )
{
	x = a;
	y = b;
	z = c;
	w = d;
}

// ------------------------------------------------------------------------------------------------------------------------------ //
// D3DX stuff.
// ------------------------------------------------------------------------------------------------------------------------------ //

// matrix stack...

HRESULT D3DXCreateMatrixStack( DWORD Flags, LPD3DXMATRIXSTACK* ppStack)
{
	
	*ppStack = new ID3DXMatrixStack;
	
	(*ppStack)->Create();
	
	return S_OK;
}

ID3DXMatrixStack::ID3DXMatrixStack( void )
{
	m_refcount[0] = 1;
	m_refcount[1] = 0;
};
		
void ID3DXMatrixStack::AddRef( int which, char *comment )
{
	Assert( which >= 0 );
	Assert( which < 2 );
	m_refcount[which]++;
};
		
ULONG ID3DXMatrixStack::Release( int which, char *comment )
{
	Assert( which >= 0 );
	Assert( which < 2 );
			
	bool deleting = false;
			
	m_refcount[which]--;
	if ( (!m_refcount[0]) && (!m_refcount[1]) )
	{
		deleting = true;
	}
			
	if (deleting)
	{
		if (m_mark)
		{
			GLMPRINTF((""))	;		// place to hang a breakpoint
		}
		delete this;
		return 0;
	}
	else
	{
		return m_refcount[0];
	}
};


HRESULT	ID3DXMatrixStack::Create()
{
	m_stack.EnsureCapacity( 16 );	// 1KB ish
	m_stack.AddToTail();
	m_stackTop = 0;				// top of stack is at index 0 currently
	
	LoadIdentity();
	
	return S_OK;
}

D3DXMATRIX* ID3DXMatrixStack::GetTop()
{
	return (D3DXMATRIX*)&m_stack[ m_stackTop ];
}

void ID3DXMatrixStack::Push()
{
	D3DMATRIX temp = m_stack[ m_stackTop ];
	m_stack.AddToTail( temp );
	m_stackTop ++;
}

void ID3DXMatrixStack::Pop()
{
	int elem = m_stackTop--;
	m_stack.Remove( elem );
}

void ID3DXMatrixStack::LoadIdentity()
{
	D3DXMATRIX *mat = GetTop();

	D3DXMatrixIdentity( mat );
}

void ID3DXMatrixStack::LoadMatrix( const D3DXMATRIX *pMat )
{
	*(GetTop()) = *pMat;
}


void ID3DXMatrixStack::MultMatrix( const D3DXMATRIX *pMat )
{

	// http://msdn.microsoft.com/en-us/library/bb174057(VS.85).aspx
	//	This method right-multiplies the given matrix to the current matrix
	//	(transformation is about the current world origin).
	//		m_pstack[m_currentPos] = m_pstack[m_currentPos] * (*pMat);
	//	This method does not add an item to the stack, it replaces the current
	//  matrix with the product of the current matrix and the given matrix.


	DXABSTRACT_BREAK_ON_ERROR();
}

void ID3DXMatrixStack::MultMatrixLocal( const D3DXMATRIX *pMat )
{
	//	http://msdn.microsoft.com/en-us/library/bb174058(VS.85).aspx
	//	This method left-multiplies the given matrix to the current matrix
	//	(transformation is about the local origin of the object).
	//		m_pstack[m_currentPos] = (*pMat) * m_pstack[m_currentPos];
	//	This method does not add an item to the stack, it replaces the current
	//	matrix with the product of the given matrix and the current matrix.


	DXABSTRACT_BREAK_ON_ERROR();
}

HRESULT ID3DXMatrixStack::ScaleLocal(FLOAT x, FLOAT y, FLOAT z)
{
	//	http://msdn.microsoft.com/en-us/library/bb174066(VS.85).aspx
	//	Scale the current matrix about the object origin.
	//	This method left-multiplies the current matrix with the computed
	//	scale matrix. The transformation is about the local origin of the object.
	//
	//	D3DXMATRIX tmp;
	//	D3DXMatrixScaling(&tmp, x, y, z);
	//	m_stack[m_currentPos] = tmp * m_stack[m_currentPos];

	DXABSTRACT_BREAK_ON_ERROR();
	return S_OK;
}


HRESULT ID3DXMatrixStack::RotateAxisLocal(CONST D3DXVECTOR3* pV, FLOAT Angle)
{
	//	http://msdn.microsoft.com/en-us/library/bb174062(VS.85).aspx
	//	Left multiply the current matrix with the computed rotation
	//	matrix, counterclockwise about the given axis with the given angle.
	//	(rotation is about the local origin of the object)

	//	D3DXMATRIX tmp;
	//	D3DXMatrixRotationAxis( &tmp, pV, angle );
	//	m_stack[m_currentPos] = tmp * m_stack[m_currentPos];
	//	Because the rotation is left-multiplied to the matrix stack, the rotation
	//	is relative to the object's local coordinate space.
	
	DXABSTRACT_BREAK_ON_ERROR();
	return S_OK;
}

HRESULT ID3DXMatrixStack::TranslateLocal(FLOAT x, FLOAT y, FLOAT z)
{
	//	http://msdn.microsoft.com/en-us/library/bb174068(VS.85).aspx
	//	Left multiply the current matrix with the computed translation
	//	matrix. (transformation is about the local origin of the object)

	//	D3DXMATRIX tmp;
	//	D3DXMatrixTranslation( &tmp, x, y, z );
	//	m_stack[m_currentPos] = tmp * m_stack[m_currentPos];

	DXABSTRACT_BREAK_ON_ERROR();
	return S_OK;
}




const char* D3DXGetPixelShaderProfile( IDirect3DDevice9 *pDevice )
{
	DXABSTRACT_BREAK_ON_ERROR();
	return "";
}

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable:4701) // potentially uninitialized local variable 'temp' used
#endif
D3DXMATRIX* D3DXMatrixMultiply( D3DXMATRIX *pOut, CONST D3DXMATRIX *pM1, CONST D3DXMATRIX *pM2 )
{
	D3DXMATRIX temp;
	
	for( int i=0; i<4; i++)
	{
		for( int j=0; j<4; j++)
		{
			temp.m[i][j]	=	(pM1->m[ i ][ 0 ] * pM2->m[ 0 ][ j ])
							+	(pM1->m[ i ][ 1 ] * pM2->m[ 1 ][ j ])
							+	(pM1->m[ i ][ 2 ] * pM2->m[ 2 ][ j ])
							+	(pM1->m[ i ][ 3 ] * pM2->m[ 3 ][ j ]);
		}
	}
	*pOut = temp;
	return pOut;
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif

// Transform a 3D vector by a given matrix, projecting the result back into w = 1
// http://msdn.microsoft.com/en-us/library/ee417622(VS.85).aspx
D3DXVECTOR3* D3DXVec3TransformCoord(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM)
{
	D3DXVECTOR3 vOut;

	vOut.x = vOut.y = vOut.z = 0.0f;
	float norm = (pM->m[0][3] * pV->x) + (pM->m[1][3] * pV->y) + (pM->m[2][3] *pV->z) + pM->m[3][3];
	if ( norm )
	{
		vOut.x = (pM->m[0][0] * pV->x + pM->m[1][0] * pV->y + pM->m[2][0] * pV->z + pM->m[3][0]) / norm;
		vOut.y = (pM->m[0][1] * pV->x + pM->m[1][1] * pV->y + pM->m[2][1] * pV->z + pM->m[3][1]) / norm;
		vOut.z = (pM->m[0][2] * pV->x + pM->m[1][2] * pV->y + pM->m[2][2] * pV->z + pM->m[3][2]) / norm;
	}

	*pOut = vOut;

	return pOut;
}


void D3DXMatrixIdentity( D3DXMATRIX *mat )
{
	for( int i=0; i<4; i++)
	{
		for( int j=0; j<4; j++)
		{
			mat->m[i][j] = (i==j) ? 1.0f : 0.0f;	// 1's on the diagonal.
		}
	}
}

D3DXMATRIX* D3DXMatrixTranslation( D3DXMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z )
{
	D3DXMatrixIdentity( pOut );
	pOut->m[3][0] = x;
	pOut->m[3][1] = y;
	pOut->m[3][2] = z;
	return pOut;
}

D3DXMATRIX* D3DXMatrixInverse( D3DXMATRIX *pOut, FLOAT *pDeterminant, CONST D3DXMATRIX *pM )
{
	Assert( sizeof( D3DXMATRIX ) == (16 * sizeof(float) ) );
	Assert( sizeof( VMatrix ) == (16 * sizeof(float) ) );
	Assert( pDeterminant == NULL );	// homey don't play that
	
	VMatrix *origM = (VMatrix*)pM;
	VMatrix *destM = (VMatrix*)pOut;
	
	bool success = MatrixInverseGeneral( *origM, *destM ); (void)success;
	Assert( success );
	
	return pOut;
}


D3DXMATRIX* D3DXMatrixTranspose( D3DXMATRIX *pOut, CONST D3DXMATRIX *pM )
{
	if (pOut != pM)
	{
		for( int i=0; i<4; i++)
		{
			for( int j=0; j<4; j++)
			{
				pOut->m[i][j] = pM->m[j][i];
			}
		}
	}
	else
	{
		D3DXMATRIX temp = *pM;
		D3DXMatrixTranspose( pOut, &temp );
	}

	return NULL;
}


D3DXPLANE* D3DXPlaneNormalize( D3DXPLANE *pOut, CONST D3DXPLANE *pP)
{
	// not very different from normalizing a vector.
	// figure out the square root of the sum-of-squares of the x,y,z components
	// make sure that's non zero
	// then divide all four components by that value
	// or return some dummy plane like 0,0,1,0 if it fails
	
	float	len = sqrt( (pP->a * pP->a) + (pP->b * pP->b) + (pP->c * pP->c) );
	if (len > 1e-10)	//FIXME need a real epsilon here ?
	{
		pOut->a = pP->a / len;		pOut->b = pP->b / len;		pOut->c = pP->c / len;		pOut->d = pP->d / len;
	}
	else
	{
		pOut->a = 0.0f;				pOut->b = 0.0f;				pOut->c = 1.0f;				pOut->d = 0.0f;
	}
	return pOut;
}


D3DXVECTOR4* D3DXVec4Transform( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV, CONST D3DXMATRIX *pM )
{
	VMatrix *mat = (VMatrix*)pM;
	Vector4D *vIn = (Vector4D*)pV;
	Vector4D *vOut = (Vector4D*)pOut;

	Vector4DMultiplyTranspose( *mat, *vIn, *vOut );

	return pOut;
}



D3DXVECTOR4* D3DXVec4Normalize( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV )
{
	Vector4D *vIn = (Vector4D*) pV;
	Vector4D *vOut = (Vector4D*) pOut;

	*vOut = *vIn;
	Vector4DNormalize( *vOut );
	
	return pOut;
}


D3DXMATRIX* D3DXMatrixOrthoOffCenterRH( D3DXMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,FLOAT zf )
{
	DXABSTRACT_BREAK_ON_ERROR();
	return NULL;
}


D3DXMATRIX* D3DXMatrixPerspectiveRH( D3DXMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf )
{
	DXABSTRACT_BREAK_ON_ERROR();
	return NULL;
}


D3DXMATRIX* D3DXMatrixPerspectiveOffCenterRH( D3DXMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf )
{
	DXABSTRACT_BREAK_ON_ERROR();
	return NULL;
}


D3DXPLANE* D3DXPlaneTransform( D3DXPLANE *pOut, CONST D3DXPLANE *pP, CONST D3DXMATRIX *pM )
{
	float *out = &pOut->a;

	// dot dot dot
	for( int x=0; x<4; x++ )
	{
		out[x] =	(pM->m[0][x] * pP->a)
				+	(pM->m[1][x] * pP->b)
				+	(pM->m[2][x] * pP->c)
				+	(pM->m[3][x] * pP->d);
	}
	
	return pOut;
}

