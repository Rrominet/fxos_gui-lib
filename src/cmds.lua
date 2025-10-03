function create_gtk_methods()
    local filepath = vim.api.nvim_buf_get_name(0)
    local start = tostring(vim.fn.getpos("'<")[2] - 1 )
    local _end = tostring(vim.fn.getpos("'>")[2])
    local command = string.format("!../scripts/write-gtk-method.py '%s' %s %s", filepath, start, _end)
    print(command)
    vim.cmd(command)
end

vim.api.nvim_create_user_command("GtkMethods", function() create_gtk_methods() end, {range=true})
vim.api.nvim_create_user_command("GtkFuncs", function() create_gtk_methods() end, {range=true})

-- create command : vim.api.nvim_create_user_command("Command Name", "lua luafunc", {})
print("mlugi.2 commands loaded.")
