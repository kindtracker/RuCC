local CFlags = "-O2"

local Sources = {
	["Source"] = "*.c",
}

local Includes = {
	["Source/Include"] = "*.h",
}

local CFiles = {}

local function Execute(Command)
	local FullCommand = Command

	local Pipe = io.popen(FullCommand, "r")
	if not Pipe then
		assert(false, "Could not execute: " .. FullCommand)
	end

	local Result = Pipe:read("*a")
	local Success, Reason, Code = Pipe:close()

	if Success ~= true and Success ~= 0 then
		assert(false, "Command failed: " .. Command .. " (" .. tostring(Code or Reason or Success) .. ")")
	end

	return Result
end

local function ListFiles(Directory, Pattern)
	local Files = {}
	local Command = "find "
		.. Quote(Directory)
		.. " -maxdepth 1 -type f -name "
		.. Quote(Pattern)
		.. " -print 2>/dev/null | sort"

	for Path in Execute(Command):gmatch("[^\r\n]+") do
		Files[#Files + 1] = Path
	end

	return Files
end

for Source, Pattern in ipairs(Sources) do
	for _, FilePath in pairs(ListFiles(Source, Pattern)) do
		CFiles[#CFiles + 1] = Path
	end
end

table.sort(CFiles)

for _, Path in pairs(CFiles) do
	local Command = string.format("cc -o Build/%s.o %s", Path, Path)
	Execute(Command)
end
