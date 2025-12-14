import Network.Socket
import Network.Socket.ByteString (send)
import qualified Data.ByteString.Char8 as BS
import Control.Monad (when)
import System.IO (hFlush, stdout)
import System.Exit (exitSuccess)

-- Higher-order function: takes a predicate and action, loops until predicate is false
loopUntil :: (String -> Bool) -> IO String -> (String -> IO ()) -> IO ()
loopUntil shouldStop getInput action = do
    input <- getInput
    if shouldStop input
        then return ()
        else do
            action input
            loopUntil shouldStop getInput action

-- Higher-order function: creates a predicate function
makePredicate :: String -> (String -> Bool)
makePredicate quitWord = (== quitWord)

-- Pure function: no side effects
isQuitMessage :: String -> Bool
isQuitMessage = (== "quit")

-- Higher-order function: gets input with prompt
getInputWithPrompt :: String -> IO String
getInputWithPrompt prompt = do
    putStr prompt
    hFlush stdout
    getLine

-- IO function: creates and connects socket
createAndConnect :: String -> Int -> IO Socket
createAndConnect serverIP serverPort = do
    sock <- socket AF_INET Stream defaultProtocol
    addr <- inet_addr serverIP
    connect sock (SockAddrInet (fromIntegral serverPort) addr)
    return sock

-- IO function: sends message through socket
sendMessage :: Socket -> String -> IO ()
sendMessage sock msg = do
    send sock (BS.pack msg)
    return ()

-- Main client function using higher-order functions
runClient :: IO ()
runClient = do
    sock <- createAndConnect "127.0.0.1" 60000  -- Using localhost for testing
    
    let quitPredicate = makePredicate "quit"
        getInput = getInputWithPrompt "Send? "
        sendAction msg = sendMessage sock msg
    
    loopUntil quitPredicate getInput sendAction
    close sock

main :: IO ()
main = runClient