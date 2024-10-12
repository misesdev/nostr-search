import { UserLoading } from "@/components/user/UserLoading"

const LoadingWeb = () => {
    return (
        <div className="w-full grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-4 md:gap-7 py-5 md:py-8 px-3 md:px-6">
            {Array.from({ length: 10 }).map((i, key) => <UserLoading key={key} />)}  
        </div>
    )
    // return (
    //     <div className="flex-col sm:p-20 w-full">
    //         <div className='mx-2 pt-10 max-w-6xl lg:pl-52 animate-pulse'>
    //             <div className='h-2.5 w-48 bg-gray-200 rounded-full mb-2.5'></div>
    //             <div className='h-3.5 w-[300px] lb:w-[360px] bg-gray-200 rounded-full mb-2.5'></div>
    //             <div className='h-2.5 w-[360px] lb:w-[560px] bg-gray-200 rounded-full mb-2.5'></div>
    //             <div className='h-2.5 w-[290px] lb:w-[530px] bg-gray-200 rounded-full mb-2.5'></div>
    //         </div>
    //         <div className='mx-2 pt-10 max-w-6xl lg:pl-52 animate-pulse'>
    //             <div className='h-2.5 w-48 bg-gray-200 rounded-full mb-2.5'></div>
    //             <div className='h-3.5 w-[300px] lb:w-[360px] bg-gray-200 rounded-full mb-2.5'></div>
    //             <div className='h-2.5 w-[360px] lb:w-[560px] bg-gray-200 rounded-full mb-2.5'></div>
    //             <div className='h-2.5 w-[290px] lb:w-[530px] bg-gray-200 rounded-full mb-2.5'></div>
    //         </div>
    //         <div className='mx-2 pt-10 max-w-6xl lg:pl-52 animate-pulse'>
    //             <div className='h-2.5 w-48 bg-gray-200 rounded-full mb-2.5'></div>
    //             <div className='h-3.5 w-[300px] lb:w-[360px] bg-gray-200 rounded-full mb-2.5'></div>
    //             <div className='h-2.5 w-[360px] lb:w-[560px] bg-gray-200 rounded-full mb-2.5'></div>
    //             <div className='h-2.5 w-[290px] lb:w-[530px] bg-gray-200 rounded-full mb-2.5'></div>
    //         </div>
    //     </div>
    // );
}

export default LoadingWeb
