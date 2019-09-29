#include <Model.hpp>
#include <Renderer.hpp>
#include <Memory.hpp>
#include <iostream>
#include <cstdio>

namespace Jam
{
	Model::Model( Renderer *p_pRenderer ) :
		m_pRenderer( p_pRenderer ),
		m_pMeshData( JAM_NULL ),
		m_MeshCount( 0U )
	{
	}

	Model::~Model( )
	{
		SafeDeleteArray< MESH_DATA >( m_pMeshData );
	}

	JAM_UINT32 Model::LoadFromFile( const std::string &p_FileName )
	{
		FILE *pModelFile = fopen( p_FileName.c_str( ), "rb" );

		if( pModelFile == JAM_NULL )
		{
			std::cout << "[Jam::Model::LoadFromFile] <ERROR> Failed to open "
				"file " << p_FileName << " for reading" << std::endl;

			return JAM_FAIL;
		}

		fseek( pModelFile, 0, SEEK_END );
		JAM_UINT32 BytesToGo = ftell( pModelFile );
		rewind( pModelFile );

		// TODO
		// Get the header
		// Then get the meta data
		// Then the meshes
		// Finally, the joints
		MODEL_HEADER ModelHeader;
		fread( &ModelHeader, sizeof( ModelHeader ), 1, pModelFile );

		BytesToGo -= sizeof( ModelHeader );

		m_MeshCount = ModelHeader.MeshCount;
		m_pMeshData = new MESH_DATA[ m_MeshCount ];

		FILE_CHUNK Chunk;
		fread( &Chunk, sizeof( FILE_CHUNK ), 1, pModelFile );

		JAM_UINT32 ChunkSkip = sizeof( FILE_CHUNK );
		JAM_UINT32 BytesRead = 0U;
		JAM_UINT32 MeshIndex = 0;

		// Get chunks
		while( BytesToGo )
		{
			BytesToGo -= ChunkSkip;
			if( ReadChunk( Chunk, pModelFile ) != JAM_OK )
			{
				return JAM_FAIL;
			}

			switch( Chunk.ID )
			{
				case MESH_CHUNK:
				{
					if( MeshIndex > ( m_MeshCount - 1 ) )
					{
						std::cout << "[Jam::Model::LoadFromFile] <ERORR> "
							"An unexpected mesh was encountered (only " <<
							m_MeshCount << " meshes in the model)" <<
							std::endl;

						return JAM_FAIL;
					}

					if( ReadMeshData( pModelFile, MeshIndex, BytesRead ) !=
						JAM_OK )
					{
						std::cout << "[Jam::Model::LoadFromFile] <ERROR> "
							"Failed to read mesh data" << std::endl;

						return JAM_FAIL;
					}
					break;
				}
				default:
				{
					std::cout << "[Jam::Model::LoadFromFile] <ERROR> Unknown "
						"chunk: " << Chunk.ID << std::endl;

					return JAM_FAIL;
				}
			}
			BytesToGo -= BytesRead;
		}

		if( pModelFile )
		{
			fclose( pModelFile );
			pModelFile = JAM_NULL;
		}

		return JAM_FAIL;
	}

	JAM_UINT32 Model::Render( )
	{
		std::cout << "[Jam::Model::Render] <ERROR> NOT IMPLEMENTED" <<
			std::endl;

		return JAM_FAIL;
	}

	JAM_UINT32 Model::ReadChunk( FILE_CHUNK &p_Chunk, FILE *p_pFile )
	{
		fread( &p_Chunk, sizeof( p_Chunk ), 1, p_pFile );

		return JAM_OK;
	}

	JAM_UINT32 Model::ReadMeshData( FILE *p_pFile,
		const JAM_UINT32 p_MeshIndex, JAM_UINT32 &p_BytesRead )
	{
		JAM_UINT32 BytesRead = 0;

		MESH_INFORMATION MeshInfo;
		fread( &MeshInfo, sizeof( MeshInfo ), 1, p_pFile );
		BytesRead += sizeof( MeshInfo );

		JAM_BYTE *pVertices = new JAM_BYTE[ MeshInfo.VertexCount ];
		fread( pVertices, sizeof( MODEL_VERTEX ), MeshInfo.VertexCount,
			p_pFile );
		BytesRead += sizeof( MODEL_VERTEX ) * MeshInfo.VertexCount;

		JAM_UINT16 *pIndices = new JAM_UINT16[ MeshInfo.IndexCount ];
		fread( pIndices, sizeof( JAM_UINT16 ), MeshInfo.IndexCount, p_pFile );
		BytesRead += sizeof( JAM_UINT16 ) * MeshInfo.IndexCount;

		m_pRenderer->RegisterPolygons( MeshInfo.VertexCount,
			MeshInfo.IndexCount, pVertices, pIndices, GL_TRIANGLES,
			0xDC566, m_pMeshData[ p_MeshIndex ].ID );

		m_pMeshData[ p_MeshIndex ].MaterialMD5 = MeshInfo.MaterialMD5;

		FILE_CHUNK Chunk;
		if( ReadChunk( Chunk, p_pFile ) != JAM_OK )
		{
			std::cout << "[Jam::Model::ReadMeshData] <ERROR> Failed to read "
				"end chunk" << std::endl;

			return JAM_FAIL;
		}

		if( Chunk.ID != FILE_END_CHUNK )
		{
			std::cout << "[Jam::Model::ReadMeshData] <ERROR> End chunk ID is "
				"not correct" << std::endl;

			return JAM_FAIL;
		}

		if( Chunk.Size != 0 )
		{
			std::cout << "[Jam::Model::ReadMeshData] <ERROR> End chunk size "
				"is not correct" << std::endl;

			return JAM_FAIL;
		}

		BytesRead += sizeof( Chunk );

		p_BytesRead = BytesRead;

		return JAM_OK;
	}
}

