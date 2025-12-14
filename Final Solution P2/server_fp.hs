import Network.Socket
import Network.Socket.ByteString (recv)
import qualified Data.ByteString.Char8 as BS
import Control.Monad (when)
import System.Exit (exitSuccess)

-- Higher-order function: processes messages until predicate is true
processUntil :: (String -> Bool) -> IO String -> (String -> IO ()) -> IO ()
processUntil shouldStop getMsg processMsg = do
    msg <- getMsg
    processMsg msg
    if shouldStop msg
        then return ()
        else processUntil shouldStop getMsg processMsg

-- Pure function: checks if message is shutdown command
isShutdownMessage :: String -> Bool
isShutdownMessage = (== "shutdown")

-- Higher-order function: creates message processor with logging
makeProcessor :: (String -> IO ()) -> String -> IO ()
makeProcessor logger msg = logger ("Received: " ++ msg)

-- IO function: creates, binds, and listens on socket
createServerSocket :: Int -> IO Socket
createServerSocket port = do
    sock <- socket AF_INET Stream defaultProtocol
    setSocketOption sock ReuseAddr 1
    bind sock (SockAddrInet (fromIntegral port) iNADDR_ANY)
    listen sock 5
    return sock

-- IO function: receives message from client socket
receiveMessage :: Socket -> IO String
receiveMessage sock = do
    msg <- recv sock 1024
    return (BS.unpack msg)

-- Main server function using higher-order functions
runServer :: IO ()
runServer = do
    listenSock <- createServerSocket 60000
    (clientSock, _) <- accept listenSock
    
    let shutdownPredicate = isShutdownMessage
        getMsg = receiveMessage clientSock
        processMsg = makeProcessor putStrLn
    
    processUntil shutdownPredicate getMsg processMsg
    
    close clientSock
    close listenSock

main :: IO ()
main = runServer