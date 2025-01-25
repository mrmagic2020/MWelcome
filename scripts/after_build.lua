function copy_lang(target, name)
    local output_dir = path.join(os.projectdir(), "bin", name)
    local lang_dir = path.join(os.projectdir(), "src", "lang")
    -- Remove existing lang directory
    if os.isdir(path.join(output_dir, "lang")) then
        os.rmdir(path.join(output_dir, "lang"))
    end
    os.cp(lang_dir, path.join(output_dir, "lang"))
end