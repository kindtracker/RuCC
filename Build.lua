local JavacFlags = "-Xlint:all"
local Output = "Build/RuCC"
local MainClass = "Main"

local Sources = {
	["Source"] = "*.java",
	["Source/RuCC"] = "*.java",
}

local Classes = "Build/classes"
local Manifest = "Build/.manifest"
local JavaFiles = {}

local function Execute(Command)
	local Pipe = io.popen(Command .. " 2>&1", "r")
	assert(Pipe, "Could not execute: " .. Command)

	local Result = Pipe:read("*a")
	local Success, Reason, Code = Pipe:close()

	assert(
		Success == true or Success == 0,
		"Command failed: " .. Command .. "\n" .. Result .. " (" .. tostring(Code or Reason or Success) .. ")"
	)

	return Result
end

local function ReadFile(Path)
	local File = io.open(Path, "r")
	if not File then
		return nil
	end

	local Content = File:read("*a")
	File:close()
	return Content
end

local function WriteFile(Path, Content)
	local File = assert(io.open(Path, "w"))
	File:write(Content)
	File:close()
end

local function ListFiles(Directory, Pattern)
	local Files = {}
	local Command = string.format("find '%s' -maxdepth 1 -type f -name '%s' -print", Directory, Pattern)

	for Path in Execute(Command):gmatch("[^\r\n]+") do
		Files[#Files + 1] = Path
	end

	return Files
end

local function Quote(Path)
	return "'" .. Path:gsub("'", "'\\''") .. "'"
end

for Source, Pattern in pairs(Sources) do
	for _, Path in ipairs(ListFiles(Source, Pattern)) do
		JavaFiles[#JavaFiles + 1] = Path
	end
end

table.sort(JavaFiles)

if #JavaFiles == 0 then
	error("No Java source files found")
end

local Fingerprint = JavacFlags .. "\n" .. MainClass .. "\n"

for _, Path in ipairs(JavaFiles) do
	local Info = Execute(string.format("stat -c '%%Y %%s' %s", Quote(Path)))

	Fingerprint = Fingerprint .. Path .. ":" .. Info
end

Execute("mkdir -p Build")

local Previous = ReadFile(Manifest)
local JarExists = io.open(Output .. ".jar", "rb")

if JarExists then
	JarExists:close()
end

if Previous == Fingerprint and JarExists then
	print("Up to date")
	return
end

Execute("rm -rf " .. Quote(Classes))
Execute("mkdir -p " .. Quote(Classes))

local Arguments = {}
for _, Path in ipairs(JavaFiles) do
	Arguments[#Args + 1] = Quote(Path)
end

WriteFile("Build/sources.args", table.concat(Arguments, "\n") .. "\n")

print("Compiling")
Execute(string.format("javac %s -d %s @Build/sources.args", JavacFlags, Quote(Classes)))

print("Packaging")
Execute(
	string.format(
		"jar --create --file %s --main-class %s -C %s .",
		Quote(Output .. ".jar"),
		Quote(MainClass),
		Quote(Classes)
	)
)

WriteFile(Manifest, Fingerprint)

print(Output .. ".jar")
