-- shader_manager.lua

---@type string
local standard_frag, standard_vertex

local pragma_signature		 	= "#pragma" 

local custom_frag_code_str	 	= pragma_signature.." ".."CUSTOM_FRAGMENT_CODE"
local custom_vertex_code_str 	= pragma_signature.." ".."CUSTOM_VERTEX_CODE"
local custom_frag_vars			= pragma_signature.." ".."CUSTOM_FRAGMENT_UNIFORMS"
local custom_uniforms_code_str 	= pragma_signature.." ".."CUSTOM_UNIFORMS"

function init()
	standard_frag = utils.read_file(
		utils.src_dir.."shaders/standart_fragment.glsl"
	)
	standard_vertex = utils.read_file(
		utils.src_dir.."shaders/standart_vertex.glsl"
	)

	if not standard_frag:find(custom_frag_code_str) then
		fatal_error("Cannot find "..custom_frag_code_str.." in fragment shader!")
	end
	if not standard_vertex:find(custom_vertex_code_str) then
		fatal_error("Cannot find "..custom_vertex_code_str.." in vertex shader!")
	end
	if not standard_vertex:find(custom_uniforms_code_str) then
		fatal_error("Cannot find "..custom_uniforms_code_str.." in shader!")
	end
end

---@param id integer
function get_base_locations(id)
	local model_loc 		= render.get_uniform_location(id, "Model")
	local view_loc 			= render.get_uniform_location(id, "View")
	local projection_loc 	= render.get_uniform_location(id, "Projection")
	local time_loc 			= render.get_uniform_location(id, "Time")
	local cam_loc 			= render.get_uniform_location(id, "CamPos")
	
	return { model_loc, view_loc, projection_loc, time_loc, cam_loc }
end

---@param path string
function process_shader(path)
	local frag_src 			= standard_frag
	local vertex_src 		= standard_vertex

	local all_src 			= utils.read_file(path)

	local frag_void 		= "fragment()"
	local vertex_void 		= "vertex()"
	local main_void			= "main()"
	local void_keyword		= "void"

	local uniform_keyword	= "uniform"

	local frag_void_find 	= all_src:find(frag_void)
	local vertex_void_find 	= all_src:find(vertex_void)

	local frag_void_len 	= frag_void:len()
	local vertex_void_len 	= frag_void:len()

	---@return string
	function get_fragment_void_code()
		if not all_src:find(frag_void) then 
			return nil 
		end
		local f_begin 	= all_src:sub(frag_void_find)
		local f_end 	= f_begin:sub(1, f_begin:find("}"))
		local f_code 	= f_end:sub(f_end:find("{") + 1, f_end:find("}") - 1)
		return f_code:gsub("\n", ""):gsub("  ", " ")
	end

	---@return string
	function get_vertex_void_code()
		if not all_src:find(vertex_void) then 
			return nil 
		end
		local v_begin 	= all_src:sub(vertex_void_find)
		local v_end 	= v_begin:sub(1, v_begin:find("}"))
		local v_code 	= v_end:sub(v_end:find("{") + 1, v_end:find("}") - 1)
		return v_code:gsub("\n", ""):gsub("  ", " ")
	end

	---@return string
	function get_custom_uniforms()
		if not all_src:find(uniform_keyword) then
			return nil 
		end
		local u_only = all_src:sub(1, all_src:find(void_keyword)-1)
		return u_only
	end

	local frag_void_code   = get_fragment_void_code()
	local vertex_void_code = get_vertex_void_code()
	local custom_uniforms  = get_custom_uniforms()

	if frag_void_code ~= nil then
		frag_src = frag_src:gsub(custom_frag_code_str, frag_void_code)
	end
	if vertex_void_code ~= nil then
		vertex_src = vertex_src:gsub(custom_vertex_code_str, vertex_void_code)
	end
	if custom_uniforms ~= nil then
		vertex_src = vertex_src:gsub(custom_uniforms_code_str, custom_uniforms)
	end
	
	return {vertex_src, frag_src}
end