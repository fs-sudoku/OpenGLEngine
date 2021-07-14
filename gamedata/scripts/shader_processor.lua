-- manager.lua

init = function()
	-- null
end

---@param code string
---@param is_vertex boolean
function process_shader(code, is_vertex) 
	for i = 1, string.len(code) do
		print(code[i])
	end
	return code
end