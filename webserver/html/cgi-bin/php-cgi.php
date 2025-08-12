#!/usr/bin/php
<?php
// Basic PHP-CGI test script

// Set content type header
header("Content-Type: text/html; charset=UTF-8");

// Get current timestamp
$timestamp = date("Y-m-d H:i:s");

// Get some environment variables that should be set by the web server
$server_name = $_SERVER['SERVER_NAME'] ?? 'Unknown';
$request_method = $_SERVER['REQUEST_METHOD'] ?? 'Unknown';
$query_string = $_SERVER['QUERY_STRING'] ?? '';
$request_uri = $_SERVER['REQUEST_URI'] ?? 'Unknown';

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PHP-CGI Test</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; background: #f5f5f5; }
        .container { background: white; padding: 30px; border-radius: 8px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        h1 { color: #333; border-bottom: 2px solid #4CAF50; padding-bottom: 10px; }
        .info-box { background: #e8f5e8; padding: 15px; border-radius: 5px; margin: 20px 0; }
        .env-var { background: #f0f0f0; padding: 10px; margin: 5px 0; border-radius: 3px; }
        .success { color: #4CAF50; font-weight: bold; }
    </style>
</head>
<body>
    <div class="container">
        <h1>🚀 PHP-CGI Test Script</h1>
        
        <div class="info-box">
            <p class="success">✅ PHP-CGI is working correctly!</p>
            <p><strong>Timestamp:</strong> <?php echo $timestamp; ?></p>
            <p><strong>PHP Version:</strong> <?php echo phpversion(); ?></p>
        </div>

        <h2>Server Environment</h2>
        <div class="env-var"><strong>SERVER_NAME:</strong> <?php echo htmlspecialchars($server_name); ?></div>
        <div class="env-var"><strong>REQUEST_METHOD:</strong> <?php echo htmlspecialchars($request_method); ?></div>
        <div class="env-var"><strong>REQUEST_URI:</strong> <?php echo htmlspecialchars($request_uri); ?></div>
        <div class="env-var"><strong>QUERY_STRING:</strong> <?php echo htmlspecialchars($query_string); ?></div>

        <h2>Request Test</h2>
        <?php if ($_SERVER['REQUEST_METHOD'] === 'GET' && !empty($_GET)): ?>
            <h3>GET Parameters:</h3>
            <?php foreach ($_GET as $key => $value): ?>
                <div class="env-var">
                    <strong><?php echo htmlspecialchars($key); ?>:</strong> 
                    <?php echo htmlspecialchars($value); ?>
                </div>
            <?php endforeach; ?>
        <?php elseif ($_SERVER['REQUEST_METHOD'] === 'POST' && !empty($_POST)): ?>
            <h3>POST Parameters:</h3>
            <?php foreach ($_POST as $key => $value): ?>
                <div class="env-var">
                    <strong><?php echo htmlspecialchars($key); ?>:</strong> 
                    <?php echo htmlspecialchars($value); ?>
                </div>
            <?php endforeach; ?>
        <?php else: ?>
            <p>Try adding some GET parameters: <code>?name=test&value=123</code></p>
        <?php endif; ?>

        <h2>Simple Form Test</h2>
        <form method="GET" action="">
            <label for="test_param">Test Parameter:</label>
            <input type="text" id="test_param" name="test_param" value="Hello World">
            <input type="submit" value="Submit GET">
        </form>
        
        <form method="POST" action="" style="margin-top: 10px;">
            <label for="post_param">POST Parameter:</label>
            <input type="text" id="post_param" name="post_param" value="POST Test">
            <input type="submit" value="Submit POST">
        </form>

        <h2>All Environment Variables</h2>
        <details>
            <summary>Click to expand $_SERVER variables</summary>
            <?php foreach ($_SERVER as $key => $value): ?>
                <div class="env-var">
                    <strong><?php echo htmlspecialchars($key); ?>:</strong> 
                    <?php echo htmlspecialchars(is_array($value) ? print_r($value, true) : $value); ?>
                </div>
            <?php endforeach; ?>
        </details>
    </div>
</body>
</html>