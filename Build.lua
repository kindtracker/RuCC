local CFlags = "-O2 -Wall"
local Output = "Build/rucc"

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
	local Command = string.format("find %s -maxdepth 1 -type f -name %s -print 2>/dev/null", Directory, Pattern)

	for Path in Execute(Command):gmatch("[^\r\n]+") do
		Files[#Files + 1] = Path
	end

	return Files
end

for Source, Pattern in pairs(Sources) do
	for _, Path in pairs(ListFiles(Source, Pattern)) do
		CFiles[#CFiles + 1] = Path
	end
end

Execute("mkdir -p Build")
for Source, _ in pairs(Sources) do
	local Command = string.format("mkdir -p Build/%s", Source)
	Execute(Command)
end

table.sort(CFiles)

local OFiles = {}
for _, Path in pairs(CFiles) do
	local OFile = string.format("Build/%s.o", Path)
	table.insert(OFiles, OFile)

	local Command = string.format("cc -c -o %s %s", OFile, Path)
	print(Path)
	Execute(Command)
end

print(Output)
local Command = string.format("cc %s -o %s", table.concat(OFiles, " "), Output)
Execute(Command)
