while ($true) {
    try {
        $client = New-Object System.Net.Sockets.TcpClient("127.0.0.1", 4444)
        $stream = $client.GetStream()

        # 15mb dữ liệu
        $data = "flood" * 3 * 1048576 

        $bytes = [System.Text.Encoding]::ASCII.GetBytes($data)
        $stream.Write($bytes, 0, $bytes.Length)
        
        # Giữ kết nối thêm 1-2 giây để mô phỏng giữ tài nguyên
        # Start-Sleep -Milliseconds 2000
        Start-Sleep -Milliseconds 200
        
        $stream.Close()
        $client.Close()
    } catch {
       
    }
}