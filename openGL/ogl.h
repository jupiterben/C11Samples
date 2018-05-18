#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/matrix.hpp>
#include <glm\gtc\type_ptr.hpp>
namespace ogl32
{
	//common types
	typedef unsigned int				uint;
	typedef int                         sizei;
	typedef std::int64_t                int64;
	typedef unsigned int				bitfield;
	enum CompareFunc
	{
		_less = GL_LESS,
		_equal = GL_EQUAL,
		_lessEqual = GL_LEQUAL,
		_greater = GL_GREATER,
		_notEqual = GL_NOTEQUAL,
		_greaterEqual = GL_GEQUAL,
		_always = GL_ALWAYS,
	};
	struct recti {
		int x; int y; sizei width; sizei height;
	};
	//macros
#define state_enable(S) \
	void enable() { glEnable(S);  }\
	void disable() { glDisable(S); } \
	bool isEnabled() { return glIsEnabled(S) == GL_TRUE; }

#define SET_VEC  set_vec(2, f);	 set_vec(3, f);	set_vec(4, f);\
	             set_vec(2, i);  set_vec(3, i);	set_vec(4, i);\
	             set_vec(2, d);  set_vec(3, d);	set_vec(4, d);

#define SET_MAT  set_mat(2  , f);  set_mat(2x3, f);  set_mat(2x4, f); \
	             set_mat(3x2, f);  set_mat(3, f);    set_mat(3x4, f);\
	             set_mat(4x2, f);  set_mat(4x3, f);  set_mat(4, f);\
	             set_mat(2, d);    set_mat(2x3, d);  set_mat(2x4, d);\
	             set_mat(3x2, d);  set_mat(3, d);	 set_mat(3x4, d);\
	             set_mat(4x2, d);  set_mat(4x3, d);  set_mat(4, d);

#define GET_VEC  get_vec(2, f); get_vec(3, f); get_vec(4, f);\
                 get_vec(2, i);	get_vec(3, i); get_vec(4, i);\
	             get_vec(2, d); get_vec(3, d); get_vec(4, d);

#define GET_MAT  get_mat(2, f);    get_mat(2x3, f);  get_mat(2x4, f);\
	             get_mat(3x2, f);  get_mat(3, f);    get_mat(3x4, f);\
	             get_mat(4x2, f);  get_mat(4x3, f);  get_mat(4, f);\
	             get_mat(2, d);    get_mat(2x3, d);  get_mat(2x4, d);\
	             get_mat(3x2, d);  get_mat(3, d);	 get_mat(3x4, d);\
	             get_mat(4x2, d);  get_mat(4x3, d);  get_mat(4, d);


	//resource	
	class VBO 
	{		
	public:
		enum Usage {
			_stream_draw = GL_STREAM_DRAW,
			_stream_read = GL_STREAM_READ,
			_stream_copy = GL_STREAM_COPY,
			_static_draw = GL_STATIC_DRAW,
			_static_read = GL_STATIC_READ,
			_static_copy = GL_STATIC_COPY,
		};
		enum MapAccess {
			_read_only = GL_READ_ONLY,
			_read_write = GL_READ_WRITE,
			_write_only = GL_WRITE_ONLY,
		};
		enum MapAccessBit {
			_read = GL_MAP_READ_BIT,
			_write = GL_MAP_WRITE_BIT,
			_persistent = GL_MAP_PERSISTENT_BIT,
			_coherent = GL_MAP_COHERENT_BIT,
			_invalidateRange = GL_MAP_INVALIDATE_RANGE_BIT,
			_invalidateBuffer = GL_MAP_INVALIDATE_BUFFER_BIT,
			_flushExplicit = GL_MAP_FLUSH_EXPLICIT_BIT,
			_unsynchronized = GL_MAP_UNSYNCHRONIZED_BIT,
		};
		enum StorageBit {
			_dynamicStorage = GL_DYNAMIC_STORAGE_BIT,
			_mapRead = GL_MAP_READ_BIT,
			_mapWrite = GL_MAP_WRITE_BIT,
			_mapPersistent = GL_MAP_PERSISTENT_BIT,
			_mapCoherent = GL_MAP_COHERENT_BIT,
			_clientStorage = GL_CLIENT_STORAGE_BIT,
		};
		VBO(uint id):handle(id) {}
		bool isValid()const { return handle != 0; }
		operator bool()const { return isValid(); }
		bool isBinded()const { return GL_TRUE==glIsBuffer(handle); } //binded once
		
		void destroy() { glDeleteBuffers(1, &handle); handle = 0; }		
		uint getHandle()const { return handle;  }
		//opengl 4.5
		void setData(const void* data, size_t sizeInByte, VBO::Usage usage = _static_draw) { glNamedBufferData(handle, sizeInByte, data, (GLenum)usage); }
		void setSubData(int offsetInBytes, size_t sizeInByte, const void *data) { glNamedBufferSubData(handle, offsetInBytes, sizeInByte, data); }
		void getSubData(int offsetInBytes, size_t sizeInByte, void *data) { glGetNamedBufferSubData(handle, offsetInBytes, sizeInByte, data); } 
		void * mapData(VBO::MapAccess access) { return  glMapNamedBuffer(handle,access); }
		bool unMapData() { return GL_TRUE == glUnmapBuffer(handle); }
	protected:
		uint handle;
	};	
	//shader	
	class Shader
	{
	public:		
		Shader(GLuint handle_) : handle(handle_) {}
		void destroy() { glDeleteShader(handle); handle = 0; }

		bool isValid()const { return glIsShader(handle) == GL_TRUE; }
		bool isVertexShader()const{ GLint iType(0);	glGetShaderiv(handle, GL_SHADER_TYPE, &iType);	return iType == GL_VERTEX_SHADER;  }
		bool isFragmentShader()const { GLint iType(0);	glGetShaderiv(handle, GL_SHADER_TYPE, &iType);	return iType == GL_FRAGMENT_SHADER; }
		bool isGeometryShader()const { GLint iType(0);	glGetShaderiv(handle, GL_SHADER_TYPE, &iType);	return iType == GL_GEOMETRY_SHADER; }

		bool isFlagDelete()const { GLint b; glGetShaderiv(handle, GL_DELETE_STATUS, &b); return b == GL_TRUE; }
		Shader& setSource(const std::string& inSrc) {
			const GLchar *source = (const GLchar*)inSrc.data();
			glShaderSource(handle, 1, &source, nullptr);
			return *this;
		}
		std::string getSource() const
		{
			std::string outSrc;
			GLint length(0);
			glGetShaderiv(handle, GL_SHADER_SOURCE_LENGTH, &length);
			if (length > 0)
			{
				GLchar *src = new GLchar[length];
				glGetShaderSource(handle, length, nullptr, src);
				outSrc = std::string(src, length);
			}
			return outSrc;
		}
		Shader& compile() { glCompileShader(handle);  return *this; }
		bool isCompiled()const {
			GLint isCompiled;
			glGetShaderiv(handle, GL_COMPILE_STATUS, &isCompiled);
			return isCompiled != 0;
		}
		std::string getInfoLog() const {
			std::string log;
			GLint length(0);
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
			if (length > 1) {
				GLchar *logMessage = new GLchar[length];
				glGetShaderInfoLog(handle, length, NULL, logMessage);
				log = logMessage;
				delete[] logMessage;
			}
			return log;
		}
		GLuint getHandle()const { return handle; }
	protected:
		GLuint handle;
	};

	class Program
	{
	public:
		Program() :handle(0) {}
		Program(uint handle_) :handle(handle_) {}
		void destroy() { glDeleteProgram(handle); handle = 0; }
		bool isValid() const { return glIsProgram(handle) == GL_TRUE; }
		operator bool()const { return isValid(); }
		uint getHandle() const { return handle;  }

		//attach shaders
		Program& attach(const Shader& shader) { glAttachShader(handle, shader.getHandle()); return *this; }
		Program& detach(const Shader& shader) { glDetachShader(handle, shader.getHandle()); return *this; }
		std::vector<Shader> getAttachedShaders() const {
			std::vector<Shader> output;
			GLint count(0);
			glGetProgramiv(handle, GL_ATTACHED_SHADERS, &count);
			if (count > 0)
			{
				GLuint* shaders = new GLuint[count];
				glGetAttachedShaders(handle, count, nullptr, shaders);
				output.assign(shaders, shaders + count);
				delete[] shaders;
			}
			return output;
		}
		Program& bindAttribLocation(int index, const std::string& str) { glBindAttribLocation(handle, index, str.data()); return *this;  }
		//link
		bool isLinked()const {	GLint isLinked;	glGetProgramiv(handle, GL_LINK_STATUS, &isLinked);	return isLinked != 0; }
		Program& link() { glLinkProgram(handle); return *this;  }

		//checks to see whether the executables contained in program can execute given the current OpenGL state
		Program& validate() { glValidateProgram(handle); return *this; }
		bool isValidated() const{	GLint status;	glGetProgramiv(handle, GL_VALIDATE_STATUS, &status);return status == GL_TRUE;}
		//called after link and validate failed
		std::string getInfoLog() {
			std::string log;
			GLint length(0);
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
			if (length > 1)
			{
				GLchar *logMessage = new GLchar[length];
				glGetProgramInfoLog(handle, length, NULL, logMessage);
				log = logMessage;
				delete[] logMessage;
			}
			return log;
		}
		//attributes and
		enum DataType {
			_float = GL_FLOAT,
			_float2 = GL_FLOAT_VEC2,
			_float3 = GL_FLOAT_VEC3,
			_float4 = GL_FLOAT_VEC4,
			_int = GL_INT,
			_int2 = GL_INT_VEC2,
			_int3 = GL_INT_VEC3,
			_int4 = GL_INT_VEC4,
			_bool = GL_BOOL,
			_bool2 = GL_BOOL_VEC2,
			_bool3 = GL_BOOL_VEC3,
			_bool4 = GL_BOOL_VEC4,
			_mat2f = GL_FLOAT_MAT2,
			_mat3f = GL_FLOAT_MAT3,
			_mat4f = GL_FLOAT_MAT4,
			_sampler2D = GL_SAMPLER_2D,
			_samplerCube = GL_SAMPLER_CUBE,
		};
		struct UAInfo {
			std::string name;
			DataType type; //type
			int arraySize; //array size
		};
		//false: -1 
		class AttributeIndex
		{
		public:
			AttributeIndex(int index, uint program) :_index(index), _program(program) {}
			bool isValid()const { return _index != -1 && _program != 0;  }
			operator bool()const { return isValid();  }
			UAInfo getInfo()
			{
				UAInfo info = { "",_float,0 };
				int nLength = Program(_program).getMaxNameLengthOfActiveUniforms();
				if (nLength > 1) {
					GLchar* nameBuffer = new GLchar[nLength];
					GLint size(0);
					GLenum type(0);
					glGetActiveAttrib(_program, _index, nLength, nullptr, &size, &type, nameBuffer);
					info.type = (DataType)type;
					info.name = nameBuffer;
					info.arraySize = size;
					delete[] nameBuffer;
				}
				return info;
			}
			int _index;
			uint _program;
		};
		class AttributeLocation 
		{
		public:
			AttributeLocation(int location, uint program) :_location(location), _program(program) {}
			int _location;
			uint _program;
		};
		int getNumberOfActiveAttribs()const {GLint nCount(0);	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &nCount);	return nCount;	}
		AttributeIndex attribute(int index) { return AttributeIndex(index, handle); }
		AttributeLocation attribute(const std::string& name) { return AttributeLocation(  getAttribLocation(name), handle );  }
		//uniforms
		//ref to the uniform		
		class UniformIndex
		{
		public:	
			UniformIndex(int index, uint program) :_index(index), _program(program) {}
			bool isValid() const { return _index !=-1 && _program!=0; }
			operator bool() const { return isValid(); }
			UAInfo getInfo() const
			{
				UAInfo info = {"",_float,0};
				int nLength = Program(_program).getMaxNameLengthOfActiveUniforms();
				if (nLength > 1) {
					GLchar* nameBuffer = new GLchar[nLength];
					GLint size(0);
					GLenum type(0);
					glGetActiveUniform(_program, _index, nLength, nullptr, &size, &type, nameBuffer);
					info.type = (DataType)type;
					info.name = nameBuffer;
					info.arraySize = size;
					delete[] nameBuffer;
				}
				return info;
			}
			std::string getName() const{
				std::string name;
				int nLength = Program(_program).getMaxNameLengthOfActiveUniforms();
				if (nLength > 1) {
					GLchar* buffer = new GLchar[nLength];
					glGetActiveUniformName(_program, _index, nLength, nullptr, buffer);
					name = buffer;
					delete[] buffer;
				}
				return name;
			}
		protected:
			int _index;
			uint _program;
		};
		class UniformLocation
		{
		public:
			UniformLocation(int location_, uint program_) : location(location_), program(program_) {}
			bool isValid() const { return location != -1 && program != 0; }
			operator bool()const { return isValid(); }
			//get uniform values
            #define get_vec(N, T) void get(glm::##T## vec##N & v) const { glGetUniform##T## v(program, location, glm::value_ptr(v) ); }
			    GET_VEC
            #undef get_vec

            #define get_mat(N, T) void get(glm::##T## mat##N & m) const { glGetUniform##T## v(program, location, glm::value_ptr(m) ); }
				GET_MAT
            #undef get_mat

				//set uniform values
            #define set_vec(N,T) void set(const glm::##T## vec##N & v) { glProgramUniform##N##T## v(program, location,1, glm::value_ptr(v)); }
				SET_VEC
            #undef set_vec
            #define set_vec(N,T) void set(const glm::##T## vec##N * v, int nCount) { glProgramUniform##N##T## v(program, location,nCount, glm::value_ptr(v[0])); }
				SET_VEC
            #undef set_vec

            #define set_mat(N,T) void set(const glm::##T## mat##N & m, bool transpos = false){ glProgramUniformMatrix##N##T## v(program, location,1, transpos ? GL_TRUE : GL_FALSE, glm::value_ptr(m)); }
				SET_MAT
            #undef set_mat
            #define set_mat(N,T) void set(const glm::##T## mat##N * m, int nCount, bool transpos = false){ glProgramUniformMatrix##N##T## v(program, location, nCount, transpos ? GL_TRUE : GL_FALSE, glm::value_ptr(m[0])); }
				SET_MAT
            #undef set_mat

		protected:
			int location;
			uint program;
		};

		int getNumberOfActiveUniforms() const {	GLint nCount(0);glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &nCount);return nCount;}
		UniformIndex uniform(int index) { return UniformIndex(index, handle); }
		int getMaxNameLengthOfActiveUniforms() const { //strlen + 1
			GLint nLength(0);
			glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nLength);
			return nLength;
		}
		UniformLocation uniform(const std::string& str) { return UniformLocation(getUniformLocation(str), handle); }
	protected:
		uint handle;
		int getUniformLocation(const std::string& str)const { return glGetUniformLocation(handle, str.data()); }
		int getAttribLocation(const std::string& str) const { return glGetAttribLocation(handle, str.data()); }
	};

	
	
	class VAO 
	{
	public:
		enum TupleSize {
			_1 = 1, _2 = 2, _3 = 3, _4 = 4, _bgra = GL_BGRA
		};
		enum PointerType {
			_float = GL_FLOAT,
		};
		VAO() :handle(0) {}
		VAO(uint id) : handle(id) {}
		bool isValid()const { return handle != 0; }
		operator bool()const { return isValid(); }
		void destroy() { glDeleteVertexArrays(1, &handle); handle = 0; }
		uint getHandle()const { return handle; }	
		auto bind() { glBindVertexArray(handle); return *this;  }		
		auto setAttributeData(const Program::AttributeLocation& loc, TupleSize tupleSize, PointerType dt, bool bNormalize, sizei strideSizeInByte, const void* pointerFirstData) {
			glVertexAttribPointer(loc._location, tupleSize, dt, bNormalize?GL_TRUE:GL_FALSE, strideSizeInByte, pointerFirstData);
			return *this;
		}
		void unBind() { glBindVertexArray(0); }
	protected:
		uint handle;
	};

	//pipeline states
	struct global
	{
		//init
		void init() { glewInit(); }
		//depth
		struct Depth
		{	
			//test
			struct Test
			{
				state_enable(GL_DEPTH_TEST)				
				void setPassFunction(CompareFunc cf) { glDepthFunc(cf);  }				
				CompareFunc getPassFunction() {	GLint cf; glGetIntegerv(GL_DEPTH_FUNC, &cf); return (CompareFunc)cf; }
			} test;
			//write
			struct Write
			{
				void enable(bool b = true) { glDepthMask(b ? GL_TRUE : GL_FALSE); }
				void disable() { glDepthMask(GL_FALSE); }
				bool isEnabled() { GLboolean b; glGetBooleanv(GL_DEPTH_WRITEMASK, &b);	return b != 0; }
			} write;
			//calculate
			struct Calculate
			{
				void setRange(double zNear = 0, double zFar = 1) { glDepthRange(zNear, zFar); }
				void getRange(double& zNear, double& zFar) {
					GLdouble range[2];
					glGetDoublev(GL_DEPTH_RANGE, range);
					zNear = range[0]; zFar = range[1];
				}
				void setOffset(float factor = 0, float units = 0) { glPolygonOffset(factor, units); }
				void getOffset(float& factor, float& units) { glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &factor);	glGetFloatv(GL_POLYGON_OFFSET_UNITS, &units); }
				struct { state_enable(GL_POLYGON_OFFSET_FILL) } offsetFill;
				struct { state_enable(GL_POLYGON_OFFSET_LINE) } offsetLine;
				struct { state_enable(GL_POLYGON_OFFSET_POINT) } offsetPoint;
			} calculate;
			//buffer
			struct Buffer
			{
				void setClearValue(double clampdVal = 1) {	glClearDepth(clampdVal); 	}
				double getClearValue() {GLdouble clampedVal; glGetDoublev(GL_DEPTH_CLEAR_VALUE, &clampedVal);return clampedVal;	}
				void clear() {	glClear(GL_DEPTH_BUFFER_BIT); }
			} buffer;	
		} depth;
		//scissor
		struct Scissor {
			struct Test{ state_enable(GL_SCISSOR_TEST) }test;
			void setBox(const recti& r) { glScissor(r.x, r.y, r.width, r.height); }
			recti getBox() const {	GLint v[4]; glGetIntegerv(GL_SCISSOR_BOX, v);
				recti r;  r.x = v[0]; r.y = v[1]; r.width = v[2]; r.height = v[3]; return r;}
		} scissor;		
		//viewport
		struct Viewport {
			void set(const recti& r) { glViewport(r.x, r.y, r.width, r.height);  }
			recti get()const { 	GLint v[4]; glGetIntegerv(GL_VIEWPORT, v);
			    recti r;  r.x = v[0]; r.y = v[1]; r.width = v[2]; r.height = v[3];
				return r;
			}
		} viewport;
		//current program
		struct ActiveProgram
		{
			struct UniformByLocation
			{
				UniformByLocation(int location_) :location(location_) {}
                #define set_vec(N,T)  void set(const glm::##T## vec##N & v) { glUniform##N##T## v(location,1, glm::value_ptr(v)); }             
				   SET_VEC
                #undef set_vec

                #define set_mat(N, T) void set(const glm::##T## mat##N & m, bool transpos = false) { glUniformMatrix##N##T## v(location, 1, transpos ? GL_TRUE : GL_FALSE, glm::value_ptr(m) ); }
				   SET_MAT
                #undef set_mat
                #define set_mat(N, T) void set(const glm::##T## mat##N * m, int nCount, bool transpos = false) { glUniformMatrix##N##T## v(location, nCount, transpos ? GL_TRUE : GL_FALSE, glm::value_ptr(m[0]) ); }
				   SET_MAT
                #undef set_mat
				
				bool isValid()const { return location != -1; }
				operator bool()const { return isValid();  }
				int location;
			};			
			uint getHandle(){ GLint curProg; glGetIntegerv(GL_CURRENT_PROGRAM, &curProg); return curProg; }
			UniformByLocation uniform(const std::string& str) { int loc = glGetUniformLocation(getHandle(), str.data()); return UniformByLocation(loc);	}
			
			template<class T>
			auto& setUniform(const std::string& str, const T& val)
			{
				uniform(str).set(val);
				return *this;
			}		
		} activeProgram;
		//buffer target
		
		struct BufferTarget {
			template<GLenum T, GLenum TB>
			struct Target {
				auto bind(const VBO& vbo) { glBindBuffer(T, vbo.getHandle()); return *this;  }
				auto unbind() { glBindBuffer(T,0); return *this; }
				VBO getBind()const{ GLint id; glGetIntegerv(TB, &id); return VBO(id); }
				auto storage(size_t sizeInByte, const void* data, bitfield storageBit) {
					glBufferStorage(T, sizeInByte, data, storageBit);  return *this;
				} //gl4.4
				template<class DT>
				auto setData(const DT* data, size_t dataLength, VBO::Usage usage = VBO::_static_draw ) { 
					glBufferData(T, sizeof(DT)*dataLength, data, (GLenum)usage);	
					return *this;
				}
				auto setSubData(int offsetInBytes, size_t sizeInByte, const void *data) { glBufferSubData(T,offsetInBytes,sizeInByte,data);return *this; }
				auto getSubData(int offsetInBytes, size_t sizeInByte, const void *data) { glGetBufferSubData(T,offsetInBytes,sizeInByte,data); }
				size_t getSizeInBytes()const { GLint size(0); glGetBufferParameteriv(T, GL_BUFFER_SIZE, &size); return size; }
				VBO::Usage getUsage()const { GLint usage; glGetBufferParameteriv(T, GL_BUFFER_USAGE, &usage); return (VBO::Usage)usage; }
				bool isImmutable()const { GLint b; glGetBufferParameteriv(T, GL_BUFFER_IMMUTABLE_STORAGE, &b); return GL_TRUE == b; }
				//map functions
				void* mapData(VBO::MapAccess access) { return glMapBuffer(T,access);  }   //map buffer data to the returned pointer
				void* mapDataRange(int offset, uint length, bitfield mapAccessBit) { glMapBufferRange(T,offset,length, mapAccessBit); }
				bool unMapData() { return GL_TRUE == glUnmapBuffer(T); }
				bool isMapped()const { GLint b; glGetBufferParameteriv(T, GL_BUFFER_MAPPED, &b); return b==GL_TRUE; }
				int64 getMapLength()const { GLint64 len; glGetBufferParameteri64v(T,GL_BUFFER_MAP_LENGTH,&len); return len; }
				int64 getMapOffset()const { GLint64 offset; glGetBufferParameteri64v(T, GL_BUFFER_MAP_OFFSET, &offset); return offset; }
				VBO::MapAccess getAccessFlag()const { GLint access; glGetBufferParameteriv(T, GL_BUFFER_ACCESS, &access); return (VBO::MapAccess)access; }
				auto flushMapRange(int offset, int length) { glFlushMappedBufferRange(T, offset, length); return *this;  }
				//
			};
			Target<GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING > array;
			Target<GL_ATOMIC_COUNTER_BUFFER, GL_ATOMIC_COUNTER_BUFFER_BINDING> atomicCounter;
			Target<GL_COPY_READ_BUFFER, GL_COPY_READ_BUFFER_BINDING > copyRead;
			Target<GL_COPY_WRITE_BUFFER, GL_COPY_WRITE_BUFFER_BINDING > copyWrite;
			Target<GL_DISPATCH_INDIRECT_BUFFER, GL_DISPATCH_INDIRECT_BUFFER_BINDING > dispatchIndirect;
			Target<GL_DRAW_INDIRECT_BUFFER, GL_DRAW_INDIRECT_BUFFER_BINDING > drawIndirect;
			Target<GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER_BINDING > element;
			Target<GL_PIXEL_PACK_BUFFER, GL_PIXEL_PACK_BUFFER_BINDING > pixelPack;
			Target<GL_PIXEL_UNPACK_BUFFER, GL_PIXEL_UNPACK_BUFFER_BINDING > pixelUnpack;
			Target<GL_QUERY_BUFFER, GL_QUERY_BUFFER_BINDING > query;
			Target<GL_SHADER_STORAGE_BUFFER, GL_SHADER_STORAGE_BUFFER_BINDING > shaderStorage;
			Target<GL_TEXTURE_BUFFER, GL_TEXTURE_BUFFER_BINDING > texture;
			Target<GL_TRANSFORM_FEEDBACK, GL_TRANSFORM_FEEDBACK_BINDING > transformFeedback;
			Target<GL_UNIFORM_BUFFER, GL_UNIFORM_BUFFER_BINDING > uniform;
		} bufferTarget;		

		bool getLastError(std::string& sError) {
			GLenum errocode = glGetError();
			const GLubyte *errString = nullptr;
			while (errocode != GL_NO_ERROR) {
				errString = gluErrorString(errocode);				
			}
			if (errString) {
				sError = (const char*)errString;
				return true;
			}
			return false;
		}
		//engine properties
		int getMaxAttributesNum()const { int n; glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n); return n; }

		void flush() { glFlush(); }

		//
		VBO createVBO() { GLuint id; glGenBuffers(1, &id); return VBO(id); }
		VBO createVBO2(){ GLuint id; glCreateBuffers(1, &id); return VBO(id); }		
		VAO createVAO() { GLuint id; glGenVertexArrays(1, &id); return VAO(id); }
		//create shaders
		Shader createVertexShader() { return glCreateShader(GL_VERTEX_SHADER); }
		Shader createGeometryShader() { return glCreateShader(GL_GEOMETRY_SHADER); }
		Shader createFragmentShader() { return glCreateShader(GL_FRAGMENT_SHADER); }
		Program createProgram() { return glCreateProgram(); }
		auto& useProgram(const Program& p) { glUseProgram(p.getHandle()); return this->activeProgram; }
		void useDefaultProgram(){ glUseProgram(0); }
		void drawArray(int nCount) { glDrawArrays(GL_TRIANGLES, 0, nCount); }
	};
};