#ifndef __JAM_MODEL_HPP__
#define __JAM_MODEL_HPP__

#include <DataTypes.hpp>
#include <MD5.hpp>
#include <string>

namespace Jam
{
	class Renderer;
	class Matrix4x4;

	const JAM_UINT32 MESH_CHUNK		= 0x00000001;
	const JAM_UINT32 JOINT_CHUNK	= 0x00000002;

#pragma pack( 1 )
	typedef struct _tagMODEL_VERTEX
	{
		JAM_FLOAT32	Position[ 3 ];
		JAM_FLOAT32	Normal[ 3 ];
		JAM_FLOAT32	ST[ 2 ];
		JAM_UINT32	JointIndices[ 4 ];
		JAM_FLOAT32	JointWeights[ 4 ];
	}MODEL_VERTEX,*PMODEL_VERTEX;

	typedef struct _tagMODEL_HEADER
	{
		char		ID[ 4 ];
		JAM_UINT32	MeshCount;
		JAM_UINT32	JointCount;
	}MODEL_HEADER,*PMODEL_HEADER;

	typedef struct _tagMESH_INFORMATION
	{
		char		Name[ 64 ];
		JAM_UINT32	VertexCount;
		JAM_UINT32	IndexCount;
		MD5_DIGEST	MaterialMD5;
	}MESH_INFORMATION,*PMESH_INFORMATION;

	typedef struct _tagMESHL_DATA
	{
		JAM_UINT32	ID;
		MD5_DIGEST	MaterialMD5;
	}MESH_DATA,*PMESH_DATA;
#pragma pack( )

	class Model
	{
	public:
		Model( Renderer *p_pRenderer );
		~Model( );

		JAM_UINT32 LoadFromFile( const std::string &p_FileName );

		JAM_UINT32 Render( );

	private:
		JAM_UINT32 ReadChunk( FILE_CHUNK &p_Chunk, FILE *p_pFile );
		JAM_UINT32 ReadMeshData( FILE *p_pFile, const JAM_UINT32 p_MeshIndex,
			JAM_UINT32 &p_BytesRead );

		Renderer	*m_pRenderer;
		MESH_DATA	*m_pMeshData;
		JAM_UINT32	m_MeshCount;
	};
}

#endif // __JAM_MODEL_HPP__

